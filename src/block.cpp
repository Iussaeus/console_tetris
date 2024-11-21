module;

#include <format>
#include <iostream>
#include <string>

module block;

import random;

namespace engine {
    block::block() : position(0, 1), type(block_type::nothing), id(engine::generate_id()), tile_offsets() {}

    block::block(const block_type type, const std::wstring& color): position(0, 1), type(type),
                                                                    id(engine::generate_id()),
                                                                    color(color), tile_offsets() {
        // note: sort of pivot
        local_grid[0][1] = 1;
        tile_offsets[0] = vec2(0, 1);

        switch (type) {
        case block_type::L_block:
            local_grid[1][1] = 1;
            tile_offsets[1] = vec2(1, 1);

            local_grid[2][1] = 1;
            tile_offsets[2] = vec2(2, 1);

            local_grid[2][2] = 1;
            tile_offsets[3] = vec2(2, 2);
            break;
        case block_type::J_block:
            local_grid[1][1] = 1;
            tile_offsets[1] = vec2(1, 1);

            local_grid[2][1] = 1;
            tile_offsets[2] = vec2(2, 1);

            local_grid[2][0] = 1;
            tile_offsets[3] = vec2(2, 0);
            break;
        case block_type::I_block:
            local_grid[1][1] = 1;
            tile_offsets[1] = vec2(1, 1);

            local_grid[2][1] = 1;
            tile_offsets[2] = vec2(2, 1);

            local_grid[3][1] = 1;
            tile_offsets[3] = vec2(3, 1);
            break;
        case block_type::O_block:
            local_grid[0][2] = 1;
            tile_offsets[1] = vec2(0, 2);

            local_grid[1][1] = 1;
            tile_offsets[2] = vec2(1, 1);

            local_grid[1][2] = 1;
            tile_offsets[3] = vec2(1, 2);
            break;
        case block_type::T_block:
            local_grid[1][0] = 1;
            tile_offsets[1] = vec2(1, 0);

            local_grid[1][1] = 1;
            tile_offsets[2] = vec2(1, 1);

            local_grid[1][2] = 1;
            tile_offsets[3] = vec2(1, 2);
            break;
        case block_type::S_block:
            local_grid[0][2] = 1;
            tile_offsets[1] = vec2(0, 2);

            local_grid[1][0] = 1;
            tile_offsets[2] = vec2(1, 0);

            local_grid[1][1] = 1;
            tile_offsets[3] = vec2(1, 1);
            break;
        case block_type::Z_block:
            local_grid[0][0] = 1;
            tile_offsets[1] = vec2(0, 0);

            local_grid[1][1] = 1;
            tile_offsets[2] = vec2(1, 1);

            local_grid[1][2] = 1;
            tile_offsets[3] = vec2(1, 2);
            break;
        case block_type::nothing:
            local_grid[0][1] = 0;
            tile_offsets[0] = vec2(0, 0);
            break;
        }
    }

    void block::on_update(float delta) {
        std::wcout << "text" << delta << "\n";
    }

    void block::init() {
        std::wcout << "init_text" << "\n";
    }

    void block::remove_tile(const vec2<int> p) {
        local_grid[p.x][p.y] = 0;
    }

    void block::update_offsets() {
        auto offset_idx = 0;
        for (int i = 0; i < local_grid.get_height(); i++) {
            for (int j = 0; j < local_grid.get_width(); j++) {
                if (local_grid[i][j] == 1) {
                    tile_offsets[offset_idx] = vec2(i, j);
                    offset_idx++;
                }
            }
        }
    }

    void block::print_data(const bool with_local_grid) const {
        std::cout << "id: " << id << " m_pos: " << position << std::endl;

        std::cout << "tile_offsets:";
        for (int i = 0; i < tile_offsets.size(); i++) {
            std::cout << tile_offsets[i] << " ";
        }

        if (with_local_grid) {
            for (int i = 0; i < local_grid.get_height(); i++) {
                for (int j = 0; j < local_grid.get_width(); j++) {
                    std::wcout << local_grid[i][j];
                }
            }
        }

        std::cout << std::endl;
    }

    void block::rotate() {
        for (int i = 0; i < local_grid.get_height(); i++) {
            for (int j = 0; j < local_grid.get_width(); j++) {
                if (i < j) {
                    std::swap(local_grid[i][j], local_grid[j][i]);
                }
            }
        }

        for (int i = 0; i < local_grid.get_height(); i++) {
            for (int j = 0; j < local_grid.get_width() / 2; j++) {
                std::swap(local_grid[i][j], local_grid[i][local_grid.get_width() - j - 1]);
            }
        }

        update_offsets();
    }

    void block::move(vec2<int> p) {
        position = p;
    }
}
