module;

#include <memory>
#include <type_traits>
#include <string>
#include <vector>

export module engine_utils;


export namespace engine {
    class entity {
    public:
        virtual ~entity() = default;
        virtual void init() = 0;
        virtual void on_update(float delta) = 0;
    };

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

    using entity_buffer = std::vector<std::shared_ptr<entity>>;
}
