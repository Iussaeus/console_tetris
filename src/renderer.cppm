module;

#include <string>
#include <vector>
#include <list>

export module renderer;

import buffer;
import block;
import engine_utils;

export namespace renderer {
    struct screen {
    private:
        buffer::buffer<std::wstring> buffer_;
        std::vector<std::wstring> debug_info_;

    public:
        screen();
        screen(int x, int y);
        ~screen();

        void init(const std::wstring&& c = L" ");
        void draw();
        void add_debug_info(const std::wstring& printable);
        [[nodiscard]] int width() const;
        [[nodiscard]] int height() const;
        static void clear();

        void update_buffer(const engine::block_buffer& blocks);
        void add_block_to_buffer(const engine::block_ptr& b);
        [[nodiscard]] buffer::buffer<std::wstring>& buffer();
    };
}
