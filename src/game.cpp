module;

#include <csignal>
#include <iostream>
#include <memory>
#include <random>

module game;

import renderer;
import renderer_utils;
import engine;
import buffer;
import utils;
import random;
import block;
import game_utils;
import input;
import engine_utils;

namespace game {
    static engine::engine engine;
    auto& input = engine.input();
    auto& actions = input.action_pairs();
    auto& screen = engine.screen();

    auto void_func = [](engine::block_ptr, float) {};
    int count = 0;
    int fall_delay = 12;
    auto controllable_func = [](const engine::block_ptr& b, float) {
        if (++count >= fall_delay - 1) {
            b->position.x++;
        }
        count %= fall_delay;

        if (input.is_action_just_pressed("down_arrow")) {
            b->position.x++;
        }
        if (input.is_action_just_pressed("right_arrow")) {
            b->position.y++;
        }
        if (input.is_action_just_pressed("left_arrow")) {
            b->position.y--;
        }
        if (input.is_action_just_pressed("rotate")) {
            b->rotate();
        }

        if (b->lowest_point().x == screen.height() - 1) {
            // b->update = void_func;
        }
    };

    bool running = true;

    auto handleSignal(int signal) -> void {
        engine.screen().clear();
        if (signal == SIGINT) {
            std::cout << "\nCaught Ctrl+C! Exiting..." << std::endl;
            running = false;
        }
    }

    auto make_random_block() -> engine::block_ptr {
        const auto& color = colors::array[engine::random(0, colors::array.size())];
        const auto& type = engine::random(0, static_cast<int>(engine::block_type::count));

        auto block = make_block(static_cast<engine::block_type>(type), color);
        block->position.y = screen.width() / 2 - 2;
        engine.push_block(block);

        return block;
    }

    auto make_controllable_block(engine::block_ptr b = make_random_block()) -> engine::block_ptr {
        b->update = controllable_func;

        return b;
    }

    void run() {
        std::signal(SIGINT, handleSignal);

        input.add_action_pair("down_arrow", "\033[B");
        input.add_action_pair("up_arrow", "\033[A");
        input.add_action_pair("right_arrow", "\033[C");
        input.add_action_pair("left_arrow", "\033[D");
        input.add_action_pair("rotate", "r");

        auto block = make_controllable_block();
        auto last_pos = block->position;

        while (engine.update() && running) {
            if (block->position != last_pos) {
                engine.debug(block->position, block->lowest_point(), screen.height());
            }

            last_pos = block->position;
        }
    }
}
