module;

#include <cstddef>
#include <memory>
#include <random>

export module game;

import block;
import renderer;

export namespace game {
    size_t total_score;
    size_t current_score;

    template <typename... Args>
    std::vector<std::shared_ptr<engine::block>> make_block_vector(Args... blocks);
    void test_block_rotation(renderer::screen& screen, engine::block&& block);
    void test_all_block_types(renderer::screen& screen);
    void test_screen_update_buffer(renderer::screen& screen,
                                   std::vector<std::shared_ptr<engine::block>>&& blocks = make_block_vector());
    void run();
}
