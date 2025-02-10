module;

#include <cstddef>
#include <memory>
#include <random>

export module game;

import block;
import renderer;
import engine;

namespace game {
    static bool running = true;

    auto make_controllable_func(engine::engine& engine);
    engine::block_ptr make_random_block(engine::engine& engine);
    engine::block_ptr make_controllable_block(engine::engine& engine);

    void add_input_actions(engine::engine& engine);

    void handle_SIGINT(int signal);
    export void run();
}
