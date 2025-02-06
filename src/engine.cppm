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
    using entity_ptr = std::shared_ptr<entity>;
    using entity_buffer = std::vector<std::shared_ptr<entity>>;

    class engine final {
    private:
        entity_buffer entities_;
        block_buffer blocks_;
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
        static bool are_blocks_colliding(const block_ptr& b1, const block_ptr& b2);
        void push_entity(entity_ptr e);
        void remove_block(const block_ptr& b);
        void print_data() const;
        bool update();
        void init();
        void render();

        entity_buffer& entities();
        input& input();
        renderer::screen& screen();

    private:
        template <typename T>
        void print_single_space(T t, std::wstringstream& ss) {
            ss << t << " ";
        }

    public:
        template <typename... Args>
        void debug(Args... printables) {
            std::wstringstream ss;
            (print_single_space(printables, ss), ...);

            screen_.add_debug_info(ss.str());
        }

    private:
        long calculate_delta();
    };
}
