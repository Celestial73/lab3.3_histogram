#pragma once

#include <chrono>

#include "../containers/Sequence.h"
#include "../sorting/ISorter.h"

template <class T>
class SortUtils {

    public:
    static const std::chrono::duration<double> sortDuration(
        SharedPtr<ds::Sequence<T>> sequence,
        SharedPtr<ISorter<T>> sorter,
        std::function<bool(const T &, const T &)> comp = std::less<T>()
        ) {
        auto start = std::chrono::high_resolution_clock::now();
        sorter->sort(sequence, comp);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        return duration;
    }
};
