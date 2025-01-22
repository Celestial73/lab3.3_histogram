#pragma once

#include "ISorter.h"

template<class T>
class ShellSorter : public ISorter<T> {
public:
    void sort(SharedPtr<ds::Sequence<T>> sequence,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override {
        shellSort(sequence, 0, sequence->getLength(), comp);

    }
    void shellSort(SharedPtr<ds::Sequence<T>> sequence, int low, int high,
        std::function<bool(const T &, const T &)> comp = std::less<T>()) {
        int size = sequence->getLength();
        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; i++) {
                T temp = sequence->get(i);
                int j;
                for (j = i; j >= gap && comp(temp, sequence->get(j - gap)); j -= gap) {
                    sequence->set(j, sequence->get(j - gap));
                }
                sequence->set(j, temp);
            }
        }
    }
};
