module;

#include <chrono>

module random;

namespace engine{
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
 }

