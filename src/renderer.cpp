module;

#include <format>
#include <memory>
#include <iostream>

module renderer;

import utils;
import buffer;
import block;
import renderer_utils;
import engine_utils;

namespace renderer {
    screen::screen(): buffer_(16, 48) {
        std::locale::global(std::locale(""));
    }

    screen::screen(const int x, const int y): buffer_(x, y) {
        std::locale::global(std::locale(""));
    }

    screen::~screen() {}

    void screen::init(const std::wstring&& c) {
        for (int i = 0; i < buffer_.height(); i++) {
            for (int j = 0; j < buffer_.width(); j++) {
                buffer_[i][j] = c + colors::reset;
            }
        }
    }

    void screen::draw() {
        auto rbegin = debug_info_.begin();
        auto rend = debug_info_.end();

        for (int i = 0; i < buffer_.height(); i++) {
            for (int j = 0; j < buffer_.width(); j++) {
                std::wcout << buffer_[i][j];
            }
            if (rbegin != rend) {
                print::space("", *rbegin);
                ++rbegin;
            }
            else {
                print::line();
            }
        }
    }

    void screen::add_debug_info(const std::wstring& printable) {
        if (debug_info_.size() >= buffer_.height() + 1)
            debug_info_.clear();
        debug_info_.push_back(printable);
    }

    int screen::width() const {
        return buffer_.width();
    }

    int screen::height() const {
        return buffer_.height();
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
        for (int i = 0; i < b->local_grid.height(); i++) {
            auto global_pos = b->position + engine::vec2(b->tile_offsets[i]);
            if ((global_pos.x >= 0 && global_pos.y >= 0) && (global_pos.x < buffer_.height() &&
                global_pos.y < buffer_.width())) {
                buffer_[global_pos.x][global_pos.y] = b->color + L'X' + colors::reset;
            }
        }
    }
}
