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

bool running = true;

void handleSignal(int signal) {
    if (signal == SIGINT) {
        std::cout << "\nCaught Ctrl+C! Exiting..." << std::endl;
        running = false;
    }
}

namespace game {
    engine::engine engine;
    auto& input = engine.input();
    auto& actions = input.action_pairs();

    void run() {
        std::signal(SIGINT, handleSignal);

        input.add_action_pair("down_arrow", "\033[B");
        input.add_action_pair("up_arrow", "\033[A");
        input.add_action_pair("right_arrow", "\033[C");
        input.add_action_pair("left_arrow", "\033[D");
        input.add_action_pair("rotate", "r");

        renderer::screen screen;

        auto block = engine::make_block(engine::block_type::J_block, colors::red);

        block->update = [&](float delta) {
            if (input.is_action_just_pressed("up_arrow")) {
                block->position.x--;
                print::line(block->position);
            }
            if (input.is_action_just_pressed("down_arrow")) {
                block->position.x++;
                print::line(block->position);
            }
            if (input.is_action_just_pressed("right_arrow")) {
                block->position.y++;
                print::line(block->position);
            }
            if (input.is_action_just_pressed("left_arrow")) {
                block->position.y--;
                print::line(block->position);
            }
            if (input.is_action_just_pressed("rotate")) {
                block->rotate();
            }
        };

        engine.push_block(block);

        while (running) {
            engine.update();
        }
    }
}
