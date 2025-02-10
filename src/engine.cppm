module;

#include <chrono>
#include <list>
#include <map>
#include <memory>
#include <vector>

export module engine;

import buffer;
import block;
import renderer;
import input;
import engine_utils;

export namespace engine {
    class engine final {
    private:
        block_buffer blocks_ = {};
        renderer::screen screen_;
        input input_;
        std::map<block_ptr, std::list<block_ptr>> collisions_ = {};

        int interval = 1000 / 30;

    public:
        engine();
        explicit engine(int frames);
        engine(int size, int width, int height);
        ~engine();


        void push_block(block_ptr b);
        void remove_block(const block_ptr& b);
        bool is_block_colliding(const block_ptr& b);
        bool will_block_collide(const block_ptr& b, vec2<int> pos);

        void print_collisions(const block_ptr& b);
        void print_data() const;

        void update();
        void render();

        block_buffer& blocks();
        input& input();
        renderer::screen& screen();

    private:
        bool are_blocks_colliding_(const block_ptr& b1, const block_ptr& b2);

    private:
        template <typename T>
        static void print_single_space(T t, std::wstringstream& ss) {
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
        void update_collisions_();
    };
}
