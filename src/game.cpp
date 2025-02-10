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
import random;
import block;
import input;
import engine_utils;

namespace game {
    auto make_controllable_func(engine::engine& engine) {
        auto& input = engine.input();
        auto& screen = engine.screen();

        static int count = 0;
        static int fall_delay = 10;
        return [&](const engine::block_ptr& b) {
            auto& p = b->position;

            if (++count >= fall_delay) {
                p.x++;
                if (engine.is_block_colliding(b)) p.x--;
            }
            count %= fall_delay;

            if (input.is_action_just_pressed("down_arrow") &&
                !engine.will_block_collide(b, p.with_x(p.x + 2))) {
                p.x++;
            }
            if (input.is_action_just_pressed("right_arrow") && b->rightest_point().y + 1 <= screen.width() - 1 &&
                !engine.will_block_collide(b, p.with_y(p.y + 2))) {
                p.y++;
                if (engine.is_block_colliding(b)) p.y--;
            }
            if (input.is_action_just_pressed("left_arrow") && b->leftest_point().y - 1 > 0 &&
                !engine.will_block_collide(b, p.with_y(p.y - 2))) {
                p.y--;
            }
            if (input.is_action_just_pressed("rotate")) {
                b->rotate();
                if (engine.is_block_colliding(b)) b->rotate_reverse();
            }

            if (engine.is_block_colliding(b)) {
                b->update = nullptr;
            }

            if (b->lowest_point().x >= screen.height() - 1) {
                b->update = nullptr;
            }
        };
    }

    engine::block_ptr make_random_block(engine::engine& engine) {
        auto& screen = engine.screen();
        const auto& color = colors::array[engine::random(0, colors::array.size())];
        const auto& type = engine::random(1, static_cast<int>(engine::block_type::count) - 1);

        auto block = make_block(static_cast<engine::block_type>(type), color);
        block->init = [&](const engine::block_ptr& b) { b->position.y = screen.width() / 2 - 2; };
        engine.push_block(block);

        return block;
    }

    engine::block_ptr make_controllable_block(engine::engine& engine) {
        engine::block_ptr b = make_random_block(engine);
        b->update = make_controllable_func(engine);

        return b;
    }

    void add_input_actions(engine::engine& engine) {
        auto& input = engine.input();

        input.add_action_pair("down_arrow", "\033[B");
        input.add_action_pair("up_arrow", "\033[A");
        input.add_action_pair("right_arrow", "\033[C");
        input.add_action_pair("left_arrow", "\033[D");
        input.add_action_pair("rotate", "r");
    }

    void handle_SIGINT(int signal) {
        running = false;
    }

    void run() {
        engine::engine engine(60);
        auto& input = engine.input();
        auto& screen = engine.screen();

        std::signal(SIGINT, handle_SIGINT);

        add_input_actions(engine);

        auto b = make_controllable_block(engine);
        auto& p = b->position;
        constexpr auto max_int = std::numeric_limits<int>::max();
        auto last_pos = engine::vec2{max_int, max_int};

        while (running) {
            if (p != last_pos) {
                // engine.debug("p:", p, "lp:", b->lowest_point(), "rp:", b->rightest_point(), "lfp:", b->leftest_point(),
                //              b->type);
            }
            if (!b->update) {
                b = make_controllable_block(engine);
            }
            engine.update();
        }
    }
}
