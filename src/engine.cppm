module;

#include <memory>
#include <vector>

export module engine;

import buffer;
import block;

export namespace engine {
    // TODO: detect collision
    // TODO: store game state(entities, buffer of locations of the blocksl
    // TODO: input handling
    // TODO: refresh rate
    // TODO: multithreading

    struct engine final {
    private:
        std::vector<std::shared_ptr<block>> m_entities_;

    public:
        engine();
        engine(int size, int width, int height);
        ~engine();

        void push_block(const std::shared_ptr<block>& b, vec2<int> position);
        void remove_block(const std::shared_ptr<block>& b);
        void print_data() const;

        const std::vector<std::shared_ptr<block>>& get_blocks() const;

    private:
        void update() const;
        std::shared_ptr<block> get_block_(size_t id) const;
    };
}
