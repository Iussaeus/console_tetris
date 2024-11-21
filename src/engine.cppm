module;

#include <memory>
#include <vector>

export module engine;

import buffer;
import block;
import renderer;
import input;
import engine_utils;

export namespace engine {
    // TODO: detect collision
    // TODO: game loop

    // TODO: refresh rate

    class engine final {
    private:
        entity_buffer entities_;
        renderer::screen screen_;
        input input_;

    public:
        engine();
        engine(int size, int width, int height);
        ~engine();

        [[nodiscard]] const block_buffer& get_blocks() const;
        [[nodiscard]] block_ptr get_block_(size_t id) const;

        void push_block(const block_ptr& b, vec2<int> position);
        void remove_block(const block_ptr& b);
        void print_data() const;
        void update() const;
    };
}
