module;

#include <cstddef>
#include <format>
#include <iostream>
#include <string>

module block;

import random;

namespace engine {
    block::block() : m_pos(0, 1), m_type(block_type::nothing), m_id(generate_id()), m_tile_offsets() {}

    block::block(const block_type type, const std::wstring& color): m_pos(0, 1), m_type(type), m_id(generate_id()),
                                                                    m_color(color), m_tile_offsets() {
        // note: sort of pivot
        m_local_grid[0][1] = 1;
        m_tile_offsets[0] = vec2(0, 1);

        switch (type) {
        case block_type::L_block:
            m_local_grid[1][1] = 1;
            m_tile_offsets[1] = vec2(1, 1);

            m_local_grid[2][1] = 1;
            m_tile_offsets[2] = vec2(2, 1);

            m_local_grid[2][2] = 1;
            m_tile_offsets[3] = vec2(2, 2);
            break;
        case block_type::J_block:
            m_local_grid[1][1] = 1;
            m_tile_offsets[1] = vec2(1, 1);

            m_local_grid[2][1] = 1;
            m_tile_offsets[2] = vec2(2, 1);

            m_local_grid[2][0] = 1;
            m_tile_offsets[3] = vec2(2, 0);
            break;
        case block_type::I_block:
            m_local_grid[1][1] = 1;
            m_tile_offsets[1] = vec2(1, 1);

            m_local_grid[2][1] = 1;
            m_tile_offsets[2] = vec2(2, 1);

            m_local_grid[3][1] = 1;
            m_tile_offsets[3] = vec2(3, 1);
            break;
        case block_type::O_block:
            m_local_grid[0][2] = 1;
            m_tile_offsets[1] = vec2(0, 2);

            m_local_grid[1][1] = 1;
            m_tile_offsets[2] = vec2(1, 1);

            m_local_grid[1][2] = 1;
            m_tile_offsets[3] = vec2(1, 2);
            break;
        case block_type::T_block:
            m_local_grid[1][0] = 1;
            m_tile_offsets[1] = vec2(1, 0);

            m_local_grid[1][1] = 1;
            m_tile_offsets[2] = vec2(1, 1);

            m_local_grid[1][2] = 1;
            m_tile_offsets[3] = vec2(1, 2);
            break;
        case block_type::S_block:
            m_local_grid[0][2] = 1;
            m_tile_offsets[1] = vec2(0, 2);

            m_local_grid[1][0] = 1;
            m_tile_offsets[2] = vec2(1, 0);

            m_local_grid[1][1] = 1;
            m_tile_offsets[3] = vec2(1, 1);
            break;
        case block_type::Z_block:
            m_local_grid[0][0] = 1;
            m_tile_offsets[1] = vec2(0, 0);

            m_local_grid[1][1] = 1;
            m_tile_offsets[2] = vec2(1, 1);

            m_local_grid[1][2] = 1;
            m_tile_offsets[3] = vec2(1, 2);
            break;
        case block_type::nothing:
            m_local_grid[0][1] = 0;
            m_tile_offsets[0] = vec2(0, 0);
            break;
        }
    }

    void block::remove_tile(vec2<int> position) {
        m_local_grid[position.x][position.y] = 0;
    }

    void block::update_offsets() {
        auto offset_idx = 0;
        for (int i = 0; i < m_local_grid.get_height(); i++) {
            for (int j = 0; j < m_local_grid.get_width(); j++) {
                if (m_local_grid[i][j] == 1) {
                    m_tile_offsets[offset_idx] = vec2(i, j);
                    offset_idx++;
                }
            }
        }
    }

    void block::print_data(bool with_local_grid) const {
        std::cout << "id: " << m_id << " m_pos: " << m_pos << std::endl;

        std::cout << "tile_offsets:";
        for (int i = 0; i < m_tile_offsets.size(); i++) {
            std::cout << m_tile_offsets[i] << " ";
        }

        std::cout << std::endl;
    }

    void block::rotate() {
        for (int i = 0; i < m_local_grid.get_height(); i++) {
            for (int j = 0; j < m_local_grid.get_width(); j++) {
                if (i < j) {
                    std::swap(m_local_grid[i][j], m_local_grid[j][i]);
                }
            }
        }

        for (int i = 0; i < m_local_grid.get_height(); i++) {
            for (int j = 0; j < m_local_grid.get_width() / 2; j++) {
                std::swap(m_local_grid[i][j], m_local_grid[i][m_local_grid.get_width() - j - 1]);
            }
        }

        update_offsets();
    }

    void block::move(vec2<int> position) {
        m_pos = position;
    }
}
