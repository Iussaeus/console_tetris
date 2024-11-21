module;

#include<memory>

export module game_utils;

import engine;
import renderer;
import renderer_utils;
import block;

export namespace utils {
    void test_all_block_types(renderer::screen& screen);
    void test_screen_update_buffer(renderer::screen& screen, const engine::block_buffer& blocks);
    void test_block_rotation(renderer::screen& screen, const engine::block_ptr& block);

    template <typename... Args>
    [[nodiscard]] engine::block_buffer make_block_buffer(Args... blocks) {
        if constexpr (sizeof...(blocks) > 0)
            return {std::make_shared<engine::block>(std::forward<Args>(blocks))...};
        else
            return {
                std::make_shared<engine::block>(engine::block_type::O_block, renderer::colors::red),
                std::make_shared<engine::block>(engine::block_type::L_block, renderer::colors::red),
                std::make_shared<engine::block>(engine::block_type::J_block, renderer::colors::red),
                std::make_shared<engine::block>(engine::block_type::S_block, renderer::colors::red),
                std::make_shared<engine::block>(engine::block_type::Z_block, renderer::colors::red),
                std::make_shared<engine::block>(engine::block_type::I_block, renderer::colors::red),
                std::make_shared<engine::block>(engine::block_type::T_block, renderer::colors::red)
            };
    }
};
