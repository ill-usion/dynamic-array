#include <iostream>
#include <vector>
#include "DynamicArray.h"
#include "ScopedTimer.h"

int main(int argc, char const *argv[])
{
    {
        timer("std::vector<int> 100,000 elements fill (us)");
        std::vector<int> v;
        for (size_t i = 0; i < 100000; i++)
        {
            v.push_back(i);
        }
    }

    {
        timer("DynamicArray<int> 100,000 elements fill (us)");
        DynamicArray<int> arr;
        for (size_t i = 0; i < 100000; i++)
        {
            arr.push(i);
        }
    }

    {
        timer("std::vector<int> 100,000 elements fill with reserve (us)");
        std::vector<int> v;
        v.reserve(100000);
        for (size_t i = 0; i < 100000; i++)
        {
            v.push_back(i);
        }
    }

    {
        timer("DynamicArray<int> 100,000 elements fill with reserve (us)");
        DynamicArray<int> arr;
        arr.reserve(100000);
        for (size_t i = 0; i < 100000; i++)
        {
            arr.push(i);
        }
    }

    {
        std::vector<int> v;
        v.reserve(1'000'000);
        for (size_t i = 0; i < 1'000'000; i++)
        {
            v.push_back(i);
        }

        timer("std::vector<int> pop 1,000,000 elements (us)");
        while (!v.empty())
            v.pop_back();
    }

    {
        DynamicArray<int> arr;
        arr.reserve(1'000'000);
        for (size_t i = 0; i < 1'000'000; i++)
        {
            arr.push(i);
        }

        timer("DynamicArray<int> pop 1,000,000 (us)");
        while (!arr.is_empty())
            arr.pop();
    }

    return 0;
}
