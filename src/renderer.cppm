module;

#include <string>

export module renderer;

import buffer;
import block;
import engine_utils;

export namespace renderer {
    struct screen {
    private:
        buffer::buffer<std::wstring> buffer_;

    public:
        screen();
        screen(int x, int y);
        ~screen();

        void init(const std::wstring&& c = L" ");
        void draw();
        static void clear();

        void update_buffer(const engine::block_buffer& blocks);
        void add_block_to_buffer(const engine::block_ptr& b);
        [[nodiscard]] buffer::buffer<std::wstring>& get_buffer();
    };
}
