module;

#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

module engine;

import renderer_utils;
import utils;

namespace engine {
    engine::engine(): entities_(16) {
        screen_.clear();
        screen_.init(L"X");
    }

    engine::engine(const int size, const int width, const int height) : entities_(size), screen_(width, height) {
        screen_.clear();
        screen_.init(L"X");
    }

    engine::~engine() {}

    void engine::init() {
        for (auto& entity : entities_) {
            entity->init();
        }
    }

    void engine::push_block(block_ptr b) {
        entities_.push_back(std::move(b));
    }

    bool engine::are_blocks_colliding(const block_ptr& b1, const block_ptr& b2) {
        const int size = b1->tile_offsets.size();

        for (int i = 0; i < size; i++) {
            const auto& off1 = b1->tile_offsets[i];
            const auto& pos1 = b1->position;

            const auto& off2 = b2->tile_offsets[i];
            const auto& pos2 = b2->position;

            if (off1 + pos1 == off2 + pos2) return true;
        }

        return false;
    }

    void engine::push_entity(entity_ptr e) {
        entities_.push_back(std::move(e));
    }

    void engine::remove_block(const std::shared_ptr<block>& b) {
        for (auto it = entities_.begin(); it != entities_.end(); ++it) {
            if (b == *it) {
                entities_.erase(it);
                return;
            }
        }
    }

    bool engine::update() {
        // todo: 1. calculate delta
        const auto delta = calculate_delta();

        // todo: 2 capture input
        input_.capture_one_input();

        // todo: 3. "entities scripts"
        for (auto& entity : entities_) {
            if (auto b = std::dynamic_pointer_cast<block>(entity)) {
                b->on_update(delta);
                b->update(b, delta);
            }
        }
        // todo: 4. update screen
        render();

        // todo: 5. update ui

        std::this_thread::sleep_until(next_execution_time_);

        return true;
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

    renderer::screen& engine::screen() {
        return screen_;
    }

    long engine::calculate_delta() {
        auto previous_time = next_execution_time_;
        next_execution_time_ += std::chrono::milliseconds(interval);

        return (next_execution_time_ - previous_time).count();
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
