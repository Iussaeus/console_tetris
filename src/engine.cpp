module;

#include <chrono>
#include <iostream>
#include <random>

module engine;

import renderer_utils;

namespace engine {
    engine::engine(): m_entities_(16) {}
    engine::engine(const int size, const int width, const int height) : m_entities_(size) {}
    engine::~engine() {}

    void engine::push_block(const std::shared_ptr<block>& b, const vec2<int> position) {
        b->m_pos = position;
        m_entities_.push_back(b);
    }

    void engine::remove_block(const std::shared_ptr<block>& b) {
        for (auto it = m_entities_.begin(); it != m_entities_.end(); ++it) {
            if (b == *it) {
                it = m_entities_.erase(it);
                return;
            }
        }
    }

    // warn it should be limited to a refresh rate
    void engine::update() const {
        for (const auto& block : m_entities_) {
            if (block->on_update) {
                block->on_update();
            }
        }
    }

    void engine::print_data() const {
        std::cout << "m_entities_: ";

        for (const auto& block : m_entities_) {
            block->print_data(false);
        }

        std::cout << std::endl;
    }

    const std::vector<std::shared_ptr<block>>& engine::get_blocks() const {
        return m_entities_;
    }

    // warn may return nullptr
    std::shared_ptr<block> engine::get_block_(size_t id) const {
        for (const auto& block : m_entities_) {
            if (id == block->m_id) {
                return block;
            }
        }
        return nullptr;
    }
}
