module;

#include <memory>
#include <type_traits>
#include <string>
#include <vector>

export module engine_utils;

export namespace engine {
    class entity {
    public:
        virtual void on_update(float delta) {};
        virtual void init() {};
    };

    template <typename T>
    concept number = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <number T>
    struct vec2 final {
    public:
        T x, y;

    public:
        vec2(): x(T()), y(T()) {}
        vec2(T x, T y): x(x), y(y) {}

        vec2& operator++(int) {
            x++;
            y++;
            return *this;
        }

        vec2& operator--(int) {
            x++;
            y++;
            return *this;
        }

        vec2 operator+(const vec2& other) const {
            auto temp = *this;
            temp.x += other.x;
            temp.y += other.y;
            return temp;
        }

        vec2 operator-(const vec2& other) const {
            auto temp = *this;
            temp.x -= other.x;
            temp.y -= other.y;
            return temp;
        }

        bool operator==(const vec2& other) const {
            return this->x == other.x && this->y == other.y;
        }

        bool operator!=(const vec2& other) const {
            return this->x != other.x || this->y != other.y;
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const vec2<T>& vec) {
        return os << "(" << vec.x << ", " << vec.y << ")";
    }

    template <typename T>
    std::wostream& operator<<(std::wostream& os, const vec2<T>& vec) {
        return os << L"(" << vec.x << L", " << vec.y << L")";
    }

    const vec2 vec2i_zero(0, 0);
    const vec2 vec2f_zero(0.0f, 0.0f);

    const vec2 vec2i_one(1, 1);
    const vec2 vec2f_one(1.0f, 1.0f);
}
