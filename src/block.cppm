module;

#include <format>
#include <functional>
#include <memory>
#include <string>

export module block;

import buffer;
import engine_utils;

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
    };

    class block : public entity {
    public:
        block();
        block(block_type type, const std::wstring& color);;

        vec2<int> position;
        const block_type type;
        const size_t id;
        std::wstring color;
        buffer::buffer<int, 4, 4> local_grid;
        std::array<vec2<int>, 4> tile_offsets;

    public:
        void on_update(float delta) override;
        void init() override;

        void remove_tile(vec2<int> p);
        void update_offsets();
        void print_data(bool with_local_grid = true) const;
        void rotate();
        void move(vec2<int> p);
    };

    // using block_ptr = std::shared_ptr<block>;
    typedef std::shared_ptr<block> block_ptr;

    using block_buffer = std::vector<std::shared_ptr<block>>;
    // typedef std::vector<std::shared_ptr<block>> block_buffer;
}
