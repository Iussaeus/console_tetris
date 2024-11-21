module;

#include <format>
#include <memory>
#include <iostream>

module renderer;

import buffer;
import block;
import renderer_utils;
import engine_utils;

namespace renderer {
    screen::screen(): buffer_(16, 48) {}
    screen::screen(const int x, const int y): buffer_(x, y) {}
    screen::~screen() {}

    void screen::init(const std::wstring&& c) {
        std::locale::global(std::locale(""));
        for (int i = 0; i < buffer_.get_height(); i++) {
            for (int j = 0; j < buffer_.get_width(); j++) {
                buffer_[i][j] = c + colors::reset;
            }
        }
    }

    void screen::draw() {
        for (int i = 0; i < buffer_.get_height(); i++) {
            for (int j = 0; j < buffer_.get_width(); j++) {
                std::wcout << buffer_[i][j];
            }
            std::wcout << std::endl;
        }
    }

    void screen::clear() {
        std::wcout << L"\033[2J\033[1;1H";
    }

    void screen::update_buffer(const engine::block_buffer& blocks) {
        for (const auto& block : blocks) {
            add_block_to_buffer(block);
        }
    }

    void screen::add_block_to_buffer(const engine::block_ptr& b) {
        for (int i = 0; i < b->local_grid.get_height(); i++) {
            auto global_pos = b->position + engine::vec2(b->tile_offsets[i]);
            if (global_pos.x > 0 || global_pos.y > 0 || global_pos.x < buffer_.get_height() || global_pos.y <
                buffer_.get_width())
                buffer_[global_pos.x][global_pos.y] = b->color + L'X' + colors::reset;
        }
    }

    buffer::buffer<std::wstring>& screen::get_buffer() {
        return buffer_;
    }
}
