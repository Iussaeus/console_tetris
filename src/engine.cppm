module;

#include <chrono>
#include <memory>
#include <vector>

export module engine;

import buffer;
import block;
import renderer;
import input;
import engine_utils;

export namespace engine {
    using entity_buffer = std::vector<std::shared_ptr<entity>>;

    class engine final {
    private:
        entity_buffer entities_;
        renderer::screen screen_;
        input input_;

        int interval = 1000 / 60;
        std::chrono::time_point<std::chrono::steady_clock> next_execution_time_ = std::chrono::steady_clock::now();

    public:
        engine();
        engine(int size, int width, int height);
        ~engine();

        [[nodiscard]] const block_buffer& get_blocks() const;
        [[nodiscard]] block_ptr get_block_(size_t id) const;

        void push_block(block_ptr b);
        void remove_block(const block_ptr& b);
        void print_data() const;
        void update();
        void render();

        entity_buffer& entities();
        input& input();
    };
}
