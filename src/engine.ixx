module;

#include <memory>
#include <random>
#include <vector>
#include <string>

export module engine;

import buffer;

export namespace engine {
	std::mt19937 random_engine(std::random_device{}());
	std::uniform_int_distribution<size_t> random_distribution;

	void set_seed(size_t seed);
	size_t random(int min, int max);
	size_t generate_id();

	struct position final {
		int x, y;

		position(int x_pos, int y_pos): x(x_pos), y(y_pos) {
		};
	};

	struct block;
	enum struct block_type;

	// TODO: create block 
	// TODO: remove block 
	// TODO: detect collision
	// TODO: give access to entities
	// TODO: store game state(entities, buffer of locations of the blocksl

	// NOTE: in engine all blocks should have width of one
	struct engine final {
	private:
		std::vector<std::shared_ptr<block>> entities_;
		buffer::buffer_2d<block> block_buffer_;

	public:
		engine();
		engine(int size, int width, int height);
		~engine();

		void add_block(std::shared_ptr<block>& b, position position);
		void remove_block(std::shared_ptr<block>& b);
		void move_block(std::shared_ptr<block>& b, position position);
		void rotate_block(block b);

		// Update stuff
		void update();

		const std::vector<block>& get_blocks();
		const buffer::buffer_2d<block>& get_block_buffer();

	private:
		void debug();
		std::shared_ptr<block>& get_block_(size_t id);
	};

	// TODO: move blocks
	// TODO: rotate blocks
	struct block final {
	public:
		block();
		block(block_type type, const std::wstring& color);;

		position position;
		const block_type type;
		const size_t id;
		std::wstring color;

	public:
		void on_update();
	};

	enum struct block_type {
		nothing = 0,
		L_block,
		I_block,
		O_block,
		T_block,
		S_block,
		Z_block,
		J_block,
	};
}
