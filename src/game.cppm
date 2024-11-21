module;

#include <cstddef>
#include <memory>
#include <random>

export module game;

import block;
import renderer;
import engine;

export namespace game {
    size_t total_score;
    size_t current_score;

    void run();
}
