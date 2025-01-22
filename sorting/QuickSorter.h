#pragma once



#include "ISorter.h"

#include "../containers/Sequence.h"



template <class T>
class QuickSorter : public ISorter<T>
{
public:
    void sort(SharedPtr<Sequence<T>> sequence,
              std::function<bool(const T &, const T &)> comp = std::less<T>()) override
    {
        quickSort(sequence, comp);
    }

private:
    int partition(SharedPtr<Sequence<T>> sequence, int low, int high,
        std::function<bool(const T &, const T &)> comp = std::less<T>())
    {
        T pivot = sequence->get(high);
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (comp(sequence->get(j), pivot))
            {
                i++;
                sequence->swap(i, j);
            }
        }

        sequence->swap(i + 1, high);
        return i + 1;
    }

    void quickSortHelper(SharedPtr<Sequence<T>> sequence, int low, int high,
        std::function<bool(const T &, const T &)> comp = std::less<T>())
    {
        if (low <  high)
        {
            int pi = partition(sequence, low, high, comp);

            quickSortHelper(sequence, low, pi - 1, comp);
            quickSortHelper(sequence, pi + 1, high, comp);
        }
    }

    void quickSort(SharedPtr<Sequence<T>> sequence,
        std::function<bool(const T &, const T &)> comp = std::less<T>())
    {
        int size = sequence->getLength();
        if (size > 1)
        {
            quickSortHelper(sequence, 0, size - 1, comp);
        }
    }
};
