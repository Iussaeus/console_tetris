module;

#include <chrono>
#include <random>

module engine;
import renderer;

namespace engine {
	void set_seed(size_t seed) {
		random_engine.seed(seed);
	}

	size_t random(int min, int max) {
		random_distribution = std::uniform_int_distribution<size_t>(min, max);
		return random_distribution(random_engine);
	}

	size_t generate_id() {
		auto now = std::chrono::high_resolution_clock::now();
		auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
		return random(0, 999999) + milli;
	}

	engine::engine(): entities_(16), block_buffer_(16, 48) {
	}

	engine::engine(const int size, const int width, const int height) : entities_(size), block_buffer_(width, height) {
	}

	engine::~engine() {
	}

	// TODO: add to buffer
	void engine::add_block(std::shared_ptr<block>& b, position position) {
		b.get()->position = position;
		entities_.push_back(b);
	}

	// TODO: remove from buffer
	void engine::remove_block(std::shared_ptr<block>& b) {
		for (auto it = entities_.begin(); it != entities_.end(); ++it) {
			if (b == *it) {
				it = entities_.erase(it);
				return;
			}
		}
	}

	block::block() : position(0, 0), type(block_type::nothing), id(0), color(renderer::colors::red) {
	}

	block::block(block_type type, const std::wstring& color): position(0, 0), type(type), id(generate_id()),
	                                                          color(color) {
	}
}
