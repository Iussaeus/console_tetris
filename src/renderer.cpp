module;

#include <format>
#include <vector>
#include <memory>
#include <iostream>

module renderer;

import buffer;
import block;
import renderer_utils;

namespace renderer {
    screen::screen(): m_buffer_(16, 48) {}
    screen::screen(const int x, const int y): m_buffer_(x, y) {}
    screen::~screen() {}

    void screen::init(const std::wstring&& c) {
        std::locale::global(std::locale(""));
        for (int i = 0; i < m_buffer_.get_height(); i++) {
            for (int j = 0; j < m_buffer_.get_width(); j++) {
                m_buffer_[i][j] = c + colors::reset;
            }
        }
    }

    void screen::draw() {
        for (int i = 0; i < m_buffer_.get_height(); i++) {
            for (int j = 0; j < m_buffer_.get_width(); j++) {
                std::wcout << m_buffer_[i][j];
            }
            std::wcout << std::endl;
        }
    }

    void screen::clear() {
        std::wcout << L"\033[2J\033[1;1H";
    }

    void screen::update_buffer(const std::vector<std::shared_ptr<engine::block>>& blocks) {
        for (const auto& block : blocks) {
            add_block_to_buffer(*block);
        }
    }

    void screen::add_block_to_buffer(const engine::block& b) {
        for (int i = 0; i < b.m_local_grid.get_height(); i++) {
            auto global_pos = b.m_pos + engine::vec2(b.m_tile_offsets[i]);
            if (global_pos.x > 0 || global_pos.y > 0 || global_pos.x < m_buffer_.get_height() || global_pos.y <
                m_buffer_.get_width())
                m_buffer_[global_pos.x][global_pos.y] = b.m_color + L'X' + colors::reset;
        }
    }
}
