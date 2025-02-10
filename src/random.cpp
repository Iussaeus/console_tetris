module;

#include <chrono>

module random;

namespace engine {
    void set_seed(size_t seed) {
        random_engine.seed(seed);
    }

    size_t random(int min, int max) {
        random_distribution = std::uniform_int_distribution<size_t>(min, max);
        return random_distribution(random_engine);
    }
}
