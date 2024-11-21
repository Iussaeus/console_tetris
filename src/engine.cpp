module;

#include <chrono>
#include <iostream>
#include <random>

module engine;

import renderer_utils;

namespace engine {
    engine::engine(): entities_(16), input_() {}
    engine::engine(const int size, const int width, const int height) : entities_(size), input_() {}
    engine::~engine() {}

    void engine::push_block(const block_ptr& b, const vec2<int> position) {
        b->position = position;
        entities_.push_back(b);
    }

    void engine::remove_block(const std::shared_ptr<block>& b) {
        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (b == *it) {
                it = entities_.erase(it);
                return;
            }
        }
    }

    // warn it should be limited to a refresh rate
    void engine::update() const {
        float delta = 0;
        for (const auto& entity : entities_) {
            entity->on_update(0);
        }
    }

    void engine::print_data() const {
        std::cout << "entities_: ";

        for (const auto& entity : entities_) {
            if (typeid(entity) == typeid(block))
                std::static_pointer_cast<block>(entity)->print_data(false);
        }

        std::cout << std::endl;
    }

    const block_buffer& engine::get_blocks() const {
        block_buffer blocks;
        blocks.reserve(entities_.size() / 2);

        for (auto& entity : entities_) {
            if (typeid(entity) == typeid(block))
                blocks.push_back(std::static_pointer_cast<block>(entity));
        }
        return blocks;
    }

    // warn may return nullptr
    block_ptr engine::get_block_(const size_t id) const {
        for (const auto& entity : entities_) {
            if (typeid(entity) == typeid(block)) {
                auto ptr = std::static_pointer_cast<block>(entity);
                if (ptr->id == id) {
                    return ptr;
                }
            }
        }
        return nullptr;
    }
}
