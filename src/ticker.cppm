module;

#include <chrono>

export module ticker;

// import engine_utils;

using namespace std::chrono_literals;
using millis = std::chrono::milliseconds;

// export namespace engine {
//     class ticker final : public entity {
//     public:
//         millis interval;
//         millis time;
//
//     private:
//         bool is_running = false;
//
//     public:
//         void start(millis duration);
//         bool is_stopped();
//         void on_update() override;
//
//     private:
//         void tick();
//     };
// };
