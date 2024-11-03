module;

#include <iostream>
#include <memory>
#include <vector>

module game;

import renderer;
import renderer_utils;
import engine;
import buffer;
import utils;
import random;
import block;


// namespace engine {
//     void block::on_update_method() { return; };
// }

namespace game {
    void run() {
        renderer::screen screen(12, 12);
        screen.init(renderer::colors::black + L"O");
    }
}

//     void test_all_block_types(renderer::screen& screen) {
//         auto blocks = make_block_vector();
//
//         for (const auto& block : blocks) {
//             screen.add_block_to_buffer(*block);
//             screen.draw();
//             screen.init(renderer::colors::black + L"O");
//             std::cout << std::endl;
//         }
//     }
//
//     void test_screen_update_buffer(renderer::screen& screen,
//                                    const std::vector<std::shared_ptr<engine::block>>& blocks) {
//         screen.update_buffer(blocks);
//
//         screen.draw();
//     }
//
//     template <typename... Args>
//     std::vector<std::shared_ptr<engine::block>> make_block_vector(Args... blocks) {
//         if constexpr (sizeof(blocks) > 0)
//             return {std::make_shared<engine::block>(std::forward<Args>(blocks))...};
//         else
//             return {
//                 std::make_shared<engine::block>(engine::block_type::O_block, renderer::colors::red),
//                 std::make_shared<engine::block>(engine::block_type::L_block, renderer::colors::red),
//                 std::make_shared<engine::block>(engine::block_type::J_block, renderer::colors::red),
//                 std::make_shared<engine::block>(engine::block_type::S_block, renderer::colors::red),
//                 std::make_shared<engine::block>(engine::block_type::Z_block, renderer::colors::red),
//                 std::make_shared<engine::block>(engine::block_type::I_block, renderer::colors::red),
//                 std::make_shared<engine::block>(engine::block_type::T_block, renderer::colors::red)
//             };
//     }
//
//     void test_block_rotation(renderer::screen& screen, engine::block&& block) {
//         block.m_pos = engine::vec2(0, 0);
//
//         screen.init(renderer::colors::black + L"O");
//         screen.add_block_to_buffer(block);
//         screen.draw();
//         std::cout << std::endl;
//
//         screen.init(renderer::colors::black + L"O");
//         block.rotate();
//         screen.add_block_to_buffer(block);
//         screen.draw();
//         std::cout << std::endl;
//
//         screen.init(renderer::colors::black + L"O");
//         block.rotate();
//         screen.add_block_to_buffer(block);
//         screen.draw();
//         std::cout << std::endl;
//
//         screen.init(renderer::colors::black + L"O");
//         block.rotate();
//         screen.add_block_to_buffer(block);
//         screen.draw();
//         std::cout << std::endl;
//
//         screen.init(renderer::colors::black + L"O");
//         block.rotate();
//         screen.add_block_to_buffer(block);
//         screen.draw();
//         std::cout << std::endl;
//     }
// }
