module;

#include <chrono>
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

module engine;

import renderer_utils;

namespace engine {
    engine::engine() {
        screen_.clear();
        screen_.init(L"X");
        blocks_.reserve(16);
    }

    engine::engine(int frames) {
        screen_.clear();
        screen_.init(L"X");
        blocks_.reserve(16);
        interval = 1000 / frames;
    }

    engine::engine(const int size, const int width, const int height) : screen_(width, height) {
        screen_.clear();
        screen_.init(L"X");
        blocks_.reserve(size);
    }

    engine::~engine() {}

    void engine::push_block(block_ptr b) {
        if (b->init) b->init(b);
        collisions_[b] = {};
        blocks_.push_back(std::move(b));
    }

    bool engine::are_blocks_colliding_(const block_ptr& b1, const block_ptr& b2) {
        if (b1 == b2) return false;

        const auto& pos1 = b1->position;
        const auto& pos2 = b2->position;

        for (const auto off1 : b1->tile_offsets) {
            for (const auto off2 : b2->tile_offsets) {
                if (pos1.with_x(pos1.x + 1) + off1 == pos2 + off2) return true;
            }
        }


        return false;
    }

    bool engine::is_block_colliding(const block_ptr& b) {
        if (blocks_.size() == 1 || collisions_[b].size() == 0) return false;

        if (collisions_[b].size() >= 1) return true;

        return false;
    }

    bool engine::will_block_collide(const block_ptr& b, vec2<int> pos) {
        if (blocks_.size() == 1 || collisions_[b].size() == 0) return false;
        auto prev_pos = b->position;
        auto would_collide = false;

        b->position = pos;
        update_collisions_();
        if (collisions_[b].size() >= 1) would_collide = true;

        b->position = prev_pos;
        update_collisions_();

        return would_collide;
    }

    void engine::update_collisions_() {
        if (blocks_.size() == 1) return;

        collisions_.clear();

        for (const auto& b1 : blocks_) {
            for (const auto& b2 : blocks_) {
                if (are_blocks_colliding_(b1, b2)) collisions_[b1].push_back(b2);
            }
        }
    }

    void engine::print_collisions(const block_ptr& b) {
        for (const auto& b1 : collisions_[b]) {
            const auto& pos = b1->position;
            const auto& to = b1->tile_offsets;
            debug("c", pos, b1->type, pos + to[0], pos + to[1], pos + to[2], pos + to[3]);
        }
    }

    void engine::remove_block(const std::shared_ptr<block>& b) {
        auto it = std::find(blocks_.begin(), blocks_.end(), b);
        blocks_.erase(it);
    }

    void engine::update() {
        auto frame_start = std::chrono::high_resolution_clock::now();

        input_.capture_one_input();

        for (auto& block : blocks_) {
            if (block) {
                if (block->update)
                    block->update(block);
            }
            update_collisions_();
        }

        render();

        auto frame_end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float, std::milli> frame_duration = frame_end - frame_start;
        if (frame_duration.count() < interval) {
            auto sleep_duration = std::chrono::milliseconds(static_cast<int>(interval - frame_duration.count()));
            std::this_thread::sleep_for(sleep_duration);
        }
    }

    void engine::render() {
        screen_.clear();
        screen_.init(colors::blue + L"O");
        screen_.update_buffer(blocks_);
        screen_.draw();
    }

    block_buffer& engine::blocks() {
        return blocks_;
    }

    input& engine::input() {
        return input_;
    }

    renderer::screen& engine::screen() {
        return screen_;
    }

    void engine::print_data() const {
        std::cout << "entities_: ";

        for (const auto& b : blocks_) {
            if (b) {
                b->print_data();
            }
        }

        std::cout << std::endl;
    }
}
