#include <iostream>
#include <chrono>

#include <memory>
#include <stdlib.h>
#include <memory>
#include <cassert>
#include "../containers/Histogram.h"
#include "../containers/ListSequence.hpp"

void testHistogram()
{
    try {
        int size = 100;

        // Populate sequence with values from 0 to 99
        int* items = new int[size];
        for (int i = 0; i < size; i++) {
            items[i] = i;
        }

        SharedPtr<Sequence<int>> sequence = SharedPtr<Sequence<int>>(new ListSequence<int>(items, size));
        int range = 10; // Assuming each bucket covers 10 values

        std::cout << "Testing Histogram construction..." << std::endl;
        Histogram<int> histogram(sequence, range);

        auto histogramString = histogram.histogramToString();
        std::cout << "Histogram output:\n" << histogramString.toStdString() << std::endl;

        delete[] items; // Clean up allocated memory

    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
    }
}

