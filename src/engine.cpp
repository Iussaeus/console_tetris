module;

#include <chrono>
#include <iostream>
#include <random>
#include <thread>

module engine;

import renderer_utils;
import utils;

namespace engine {
    engine::engine(): entities_(16) {}

    engine::engine(const int size, const int width, const int height) : entities_(size), screen_(width, height) {
        screen_.init(L"X");
        screen_.draw();
    }

    engine::~engine() {}

    void engine::push_block(block_ptr b) {
        entities_.push_back(std::move(b));
    }

    void engine::remove_block(const std::shared_ptr<block>& b) {
        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (b == *it) {
                entities_.erase(it);
                return;
            }
        }
    }

    void engine::update() {
        // todo: 1. calculate delta
        auto previous_time = next_execution_time_;
        next_execution_time_ += std::chrono::milliseconds(interval);

        auto delta = (next_execution_time_ - previous_time).count();
        // todo: 2a. update "physics"

        // todo: 2b. capture input
        input_.capture_one_input();

        // todo: 3. "entities scripts"
        for (auto& entity : entities_) {
            auto b = std::dynamic_pointer_cast<block>(entity);
            if (b) {
                b->update(delta);
            }
        }
        // todo: 4. update screen
        render();

        // todo: 5. update ui

        std::this_thread::sleep_until(next_execution_time_);
    }

    // todo: render
    void engine::render() {
        screen_.clear();
        screen_.init(colors::blue + L"O");

        const auto& blocks = get_blocks();
        screen_.update_buffer(blocks);

        screen_.draw();
    }

    entity_buffer& engine::entities() {
        return entities_;
    }

    input& engine::input() {
        return input_;
    }

    void engine::print_data() const {
        std::cout << "entities_: ";

        for (const auto& entity : entities_) {
            if (const auto b = std::dynamic_pointer_cast<block>(entity)) {
                b->print_data();
            }
        }

        std::cout << std::endl;
    }

    const block_buffer& engine::get_blocks() const {
        static block_buffer blocks;
        blocks.clear();
        blocks.reserve(entities_.size() / 2);

        for (auto& entity : entities_) {
            if (const auto b = std::dynamic_pointer_cast<block>(entity)) {
                blocks.push_back(b);
            }
        }

        return blocks;
    }

    /// @return block if found, nullptr if not
    block_ptr engine::get_block_(const size_t id) const {
        for (const auto& entity : entities_) {
            const auto ptr = std::dynamic_pointer_cast<block>(entity);

            if (ptr->id == id) {
                return ptr;
            }
        }
        return nullptr;
    }
}
