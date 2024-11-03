module;

#include <format>
#include <functional>
#include <string>

export module block;

import buffer;

export namespace engine {
    template <typename T>
    struct vec2 final {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "vec2 can only be instantiated with integral or floating-point types.");

    public:
        T x, y;

    public:
        vec2(): x(T()), y(T()) {}
        vec2(T x_pos, T y_pos): x(x_pos), y(y_pos) {}

        vec2 operator+(const vec2& other) const {
            return vec2(this->x + other.x, this->y + other.y);
        }

        vec2 operator-(const vec2& other) const {
            return vec2(this->x - other.x, this->y - other.y);
        }

        bool operator==(const vec2& other) const {
            return this->x == other.x && this->y == other.y;
        }

        bool operator!=(const vec2& other) const {
            return this->x != other.x && this->y != other.y;
        }

        inline friend std::ostream& operator<<(std::ostream& os, const engine::vec2<T>& vec) {
            return os << std::string("(") << vec.x << ", " << vec.y << ")";
        };
    };

    const vec2 vec2i_zero(0, 0);
    const vec2 vec2f_zero(0.0f, 0.0f);

    const vec2 vec2i_one(1, 1);
    const vec2 vec2f_one(1.0f, 1.0f);


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

    struct block final {
    public:
        block();
        block(block_type type, const std::wstring& color);;

        vec2<int> m_pos;
        const block_type m_type;
        const size_t m_id;
        std::wstring m_color;
        buffer::buffer<int, 4, 4> m_local_grid;
        std::array<vec2<int>, 4> m_tile_offsets;

        std::function<void()> on_update;

    public:
        /// takes in coords in it's local matrix
        // void on_update_method();
        void remove_tile(vec2<int> position);
        void update_offsets();
        void print_data(bool with_local_grid = true) const;
        void rotate();
        void move(vec2<int> position);
    };
}
