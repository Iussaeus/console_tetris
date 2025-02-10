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
    engine::engine engine(60);
    auto& input = engine.input();
    auto& screen = engine.screen();


    int count = 0;
    int fall_delay = 10;
    auto controllable_func = [](const engine::block_ptr& b) {
        if (++count >= fall_delay) {
            b->position.x++;
            if (engine.is_block_colliding(b)) b->position.x--;
        }
        count %= fall_delay;

        if (input.is_action_just_pressed("down_arrow")) {
            b->position.x++;
            if (engine.is_block_colliding(b)) b->position.x--;
        }
        if (input.is_action_just_pressed("right_arrow") && b->position.y + 4 < screen.width()) {
            b->position.y++;
        }
        if (input.is_action_just_pressed("left_arrow") && b->position.y - 2 > 0) {
            b->position.y--;
        }
        if (input.is_action_just_pressed("rotate")) {
            b->rotate();
        }

        if (engine.is_block_colliding(b)) {
            b->update = nullptr;
        }

        if (b->lowest_point().x >= screen.height() - 1) {
            b->update = nullptr;
        }
        if (engine.is_block_colliding(b)) {
            const auto& pos = b->position;
            const auto& to = b->tile_offsets;
            engine.debug("b", pos, b->type, pos + to[0], pos + to[1], pos + to[2], pos + to[3], b->lowest_point());
            engine.print_collisions(b);
        }
    };

    bool running = true;

    auto handle_SIGINT(int signal) -> void {
        if (signal == SIGINT) {
            running = false;
        }
    }

    auto make_random_block() -> engine::block_ptr {
        const auto& color = colors::array[engine::random(0, colors::array.size())];
        const auto& type = engine::random(1, static_cast<int>(engine::block_type::count) - 1);

        auto block = make_block(static_cast<engine::block_type>(type), color);
        block->init = [](const engine::block_ptr& b) { b->position.y = screen.width() / 2 - 2; };
        engine.push_block(block);

        return block;
    }

    auto make_controllable_block(engine::block_ptr b = make_random_block()) -> engine::block_ptr {
        b->update = controllable_func;

        return b;
    }

    void add_input_actions() {
        input.add_action_pair("down_arrow", "\033[B");
        input.add_action_pair("up_arrow", "\033[A");
        input.add_action_pair("right_arrow", "\033[C");
        input.add_action_pair("left_arrow", "\033[D");
        input.add_action_pair("rotate", "r");
    }

    void run() {
        std::signal(SIGINT, handle_SIGINT);

        add_input_actions();

        auto block = make_controllable_block();
        constexpr auto max_int = std::numeric_limits<int>::max();
        auto last_pos = engine::vec2{max_int, max_int};

        while (running) {
            if (block->position != last_pos) {
                engine.debug(block->position, block->lowest_point(), block->type,
                             engine.is_block_colliding(block) ? "true" : "false");
            }
            if (!block->update) {
                block = make_controllable_block();
                // for (const auto& b : engine.blocks()) {
                //     engine.debug(b->id);
                // }
            }
            last_pos = block->position;
            engine.update();
        }
    }
}
