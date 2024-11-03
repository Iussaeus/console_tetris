module;

#include <memory>
#include <string>
#include <vector>

export module renderer;

import buffer;
import block;

namespace renderer {
    export struct screen {
    private:
        buffer::buffer<std::wstring> m_buffer_;

    public:
        screen();
        screen(int x, int y);
        ~screen();

        void init(const std::wstring&& c = L" ");
        void draw();
        static void clear();

        void update_buffer(const std::vector<std::shared_ptr<engine::block>>& blocks);
        void add_block_to_buffer(const engine::block& b);

    private:
    };
}
