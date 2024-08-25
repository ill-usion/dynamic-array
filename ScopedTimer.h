#pragma once

#include <iostream>
#include <chrono>

#define timer(name) ScopedTimer _t(name)
#define seconds_timer(name) ScopedTimer<std::chrono::seconds> _t(name)

template<typename Unit = std::chrono::microseconds>
class ScopedTimer {
public:
    std::string_view name;
    std::chrono::high_resolution_clock::time_point start;

    ScopedTimer(std::string_view timer_name=""): name(timer_name)
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~ScopedTimer()
    {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<Unit>(end - start).count();
        std::cout << "==========\n";
        std::cout << std::format("[Timer: {}] elapsed {}\n", name, elapsed);
        std::cout << "==========\n";
    }
};
