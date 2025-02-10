module;

#include <iostream>
#include <memory>

module game_utils;

import renderer;
import block;
import engine_utils;
import engine;

namespace utils {
    void test_all_block_types(renderer::screen& screen) {
        auto blocks = make_block_buffer();

        for (const auto& block : blocks) {
            block->print_data(true);
        }
    }

    void test_screen_update_buffer(renderer::screen& screen, const engine::block_buffer& blocks) {
        screen.update_buffer(blocks);
        screen.draw();
    }

    void test_block_rotation(renderer::screen& screen, const engine::block_ptr& block) {
        block->position = engine::vec2(0, 0);

        screen.init(colors::black + L"O");
        screen.add_block_to_buffer(block);
        screen.draw();
        std::wcout << std::endl;

        screen.init(colors::black + L"O");
        block->rotate();
        screen.add_block_to_buffer(block);
        screen.draw();
        std::wcout << std::endl;

        screen.init(colors::black + L"O");
        block->rotate();
        screen.add_block_to_buffer(block);
        screen.draw();
        std::wcout << std::endl;

        screen.init(colors::black + L"O");
        block->rotate();
        screen.add_block_to_buffer(block);
        screen.draw();
        std::wcout << std::endl;

        screen.init(colors::black + L"O");
        block->rotate();
        screen.add_block_to_buffer(block);
        screen.draw();
        std::wcout << std::endl;
    }
};
