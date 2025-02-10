module;

#include <format>
#include <functional>
#include <memory>
#include <string>

export module block;

import buffer;
import engine_utils;
import renderer_utils;

export namespace engine {
    enum struct block_type {
        nothing = 0,
        L_block,
        I_block,
        O_block,
        T_block,
        S_block,
        Z_block,
        J_block,
        count
    };

    std::wostream& operator<<(std::wostream& os, block_type value) {
        switch (value) {
        case block_type::nothing: os << L"nothing";
            break;
        case block_type::L_block: os << L"L_block";
            break;
        case block_type::I_block: os << L"I_block";
            break;
        case block_type::O_block: os << L"O_block";
            break;
        case block_type::T_block: os << L"T_block";
            break;
        case block_type::S_block: os << L"S_block";
            break;
        case block_type::Z_block: os << L"Z_block";
            break;
        case block_type::J_block: os << L"J_block";
            break;
        case block_type::count: os << L"count";
            break;
        default: os << L"unknown";
            break;
        }
        return os;
    }

    class block final {
    public:
        explicit block(block_type type = block_type::nothing, const std::wstring& color = colors::red);

        vec2<int> position;
        const block_type type;
        const size_t id;
        std::wstring color;
        bool is_enabled;
        buffer::buffer<int, 4, 4> local_grid;
        std::array<vec2<int>, 4> tile_offsets;
        std::function<void(std::shared_ptr<block>& b)> update = nullptr;
        std::function<void(std::shared_ptr<block>& b)> init = nullptr;

    public:
        void remove_tile(vec2<int> p);
        void print_data(bool with_local_grid = true) const;
        void rotate();
        vec2<int> lowest_point() const;

    private:
        void update_offsets();
    };

    using block_ptr = std::shared_ptr<block>;
    using block_buffer = std::vector<std::shared_ptr<block>>;

    block_ptr make_block(block_type type = block_type::nothing, renderer::color color = colors::red);
}
