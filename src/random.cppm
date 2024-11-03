module;

#include<cstddef>
#include<random>

export module random;

export namespace engine{
    std::mt19937 random_engine(std::random_device{}());
    std::uniform_int_distribution<size_t> random_distribution;

    void set_seed(size_t seed);
    size_t random(int min, int max);
    size_t generate_id();
 }

