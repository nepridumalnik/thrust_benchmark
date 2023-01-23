#include <thrust/device_vector.h>
#include <thrust/transform.h>

#include <iostream>
#include <vector>
#include <chrono>

class Timer
{
public:
    Timer() : start_time_{std::chrono::high_resolution_clock::now()}
    {
    }

    ~Timer()
    {
        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_);
        std::cout << "duration: " << duration.count() << " milliseconds" << std::endl;
    }

private:
    const std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};

template <typename T>
T add(const T &x, const T &y) { return x + y; }

template <typename T>
T mul(const T &x, const T &y) { return x * y; }

template <typename T>
T div(const T &x, const T &y) { return x / y; }

template <typename T>
T sub(const T &x, const T &y) { return x - y; }

template <typename T>
void apply_function(T (*fun)(const T &, const T &))
{
    thrust::device_vector<T> vec1{30 << 20};
    thrust::device_vector<T> vec2{vec1.size()};

    thrust::fill(vec1.begin(), vec1.end(), 1.0f);
    thrust::fill(vec2.begin(), vec2.end(), 2.0f);

    thrust::device_vector<T> result{vec1.size()};

    thrust::transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(), fun);

    std::vector<T> result_host(result.size());

    thrust::copy(result.begin(), result.end(), result_host.begin());
}

template <typename T>
void test()
{
    {
        std::cout << "add: " << std::endl;
        Timer t;
        apply_function(add<T>);
    }

    {
        std::cout << "mul: " << std::endl;
        Timer t;
        apply_function(mul<T>);
    }

    {
        std::cout << "div: " << std::endl;
        Timer t;
        apply_function(div<T>);
    }

    {
        std::cout << "sub: " << std::endl;
        Timer t;
        apply_function(sub<T>);
    }
}

int main(int argc, char const *argv[])
{
    std::cout << "Start!" << std::endl;

    std::cout << "Doubles:" << std::endl;
    test<double>();

    std::cout << "Floats:" << std::endl;
    test<float>();

    std::cout << "uint64_t:" << std::endl;
    test<uint64_t>();

    std::cout << "uint32_t:" << std::endl;
    test<uint32_t>();

    std::cout << "uint16_t:" << std::endl;
    test<uint16_t>();

    std::cout << "uint8:" << std::endl;
    test<uint8_t>();

    std::cout << "Done!" << std::endl;

    return 0;
}
