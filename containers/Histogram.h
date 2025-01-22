#pragma once

#include "HashTable.h"
#include  "../sorting/QuickSorter.h"
#include <iostream>
#include <QString>
#include <sstream>

template <typename T>
using Sqrt = std::function<T(const T&)>;

template <typename T>
class Histogram
{
private:
    HashTable<int, int> table;
    SharedPtr<Sequence<T>> seq;
public:

    Histogram<T>(SharedPtr<Sequence<T>> baseSequence, int range, std::function<bool(const T &, const T &)> comp = std::less<T>())
    {
        seq = baseSequence->copy();
        SharedPtr<ISorter<T>> sorter = SharedPtr<ISorter<T>>(new QuickSorter<T>());
        sorter->sort(seq, comp);
        if (seq->getLength() == 0)
        {
            throw std::runtime_error("Sequence is empty.");
        }
        else if (range <1)
        {
            throw std::runtime_error("Range must be greater than zero.");
        }
        int ind=0;
        int start = 0;

        for (int i = 0; i < seq->getLength(); i++)
        {
            if (comp(seq->get(start) + range-1, seq->get(i)))
            {
                table.add(ind, start);
                ind++;
                start = i;
            }
        }
    }


    explicit Histogram(int capacity = 13) : table(capacity) {}


    QString histogramToString() {
        std::ostringstream oss;
        auto iterator = table.getIterator();
        iterator->moveNext();
        int previousStartIndex = iterator->getCurrentValue();
        int setStartIndex = 0;
        int setNumber = 0;
        while (iterator->moveNext())
        {
            setNumber = iterator->getCurrentKey();
            setStartIndex = iterator->getCurrentValue();
            oss << "Set #" << iterator->getCurrentKey() << ": " << std::endl;
            oss << "Count = " << setStartIndex-previousStartIndex << ". Elements: {";
            for (int i = previousStartIndex; i < setStartIndex; i++){
                oss << seq->get(i) << " ";
            }
            oss << "}" << std:: endl;
            PrintStatistics(oss, previousStartIndex, setStartIndex);
            previousStartIndex = setStartIndex;
            oss << "\n";
        }
        oss << "Set #" << setNumber+1 << ": " << std::endl;
        oss << "Count = " << seq->getLength()-previousStartIndex << ". Elements: {";
        for (int i = previousStartIndex; i < seq->getLength(); i++){
            oss << seq->get(i) << " ";
        }
        oss << "}" << std:: endl;
        PrintStatistics(oss, previousStartIndex, seq->getLength());
        oss << "\n";
        return QString::fromStdString(oss.str());
    }

    T Mean(int startIndex, int endIndex)
    {
        T sum = 0;
        int size = endIndex-startIndex;
        if (size == 0)
        {
            throw std::runtime_error("Cannot calculate mean of an empty subsequence.");
        }
        for (int i = startIndex; i < endIndex; ++i)
        {
            sum += seq->get(i);
        }
        return sum / size;
    }

    T StandardDeviation(int startIndex, int endIndex, Sqrt<T> sqrt = [](const T& x) { return std::sqrt(x); })
    {
        int size = endIndex - startIndex;
        if (size == 0) {
            throw std::runtime_error("Cannot calculate standard deviation of an empty subsequence.");
        }

        T mean = Mean(startIndex, endIndex);
        T sumOfSquares = 0;

        for (int i = startIndex; i < endIndex; ++i) {
            T deviation = seq->get(i) - mean;
            sumOfSquares += deviation * deviation;
        }

        return sqrt(sumOfSquares / size);
    }

    T RootMeanSquare(int startIndex, int endIndex, Sqrt<T> sqrt = [](const T& x) { return std::sqrt(x); })
    {
        int size = endIndex - startIndex;
        if (size == 0) {
            throw std::runtime_error("Cannot calculate root mean square of an empty subsequence.");
        }

        T sumOfSquares = 0;
        for (int i = startIndex; i < endIndex; ++i) {
            sumOfSquares += seq->get(i) * seq->get(i);
        }
        return sqrt(sumOfSquares / size);
    }

    T Min(int startIndex, int endIndex)
    {
        if (endIndex - startIndex == 0) {
            throw std::runtime_error("Cannot calculate minimum of an empty subsequence.");
        }

        T minValue = seq->get(startIndex);
        for (int i = startIndex + 1; i < endIndex; ++i) {
            if (seq->get(i) < minValue) {
                minValue = seq->get(i);
            }
        }
        return minValue;
    }

    T Max(int startIndex, int endIndex)
    {
        if (endIndex - startIndex == 0) {
            throw std::runtime_error("Cannot calculate maximum of an empty subsequence.");
        }

        T maxValue = seq->get(startIndex);
        for (int i = startIndex + 1; i < endIndex; ++i) {
            if (seq->get(i) > maxValue) {
                maxValue = seq->get(i);
            }
        }
        return maxValue;
    }

    T Median(int startIndex, int endIndex)
    {
        int size = endIndex - startIndex;
        if (size == 0) {
            throw std::runtime_error("Cannot calculate median of an empty subsequence.");
        }

        int midIndex = startIndex + size / 2;
        if (size % 2 == 0) {
            return (seq->get(midIndex - 1) + seq->get(midIndex)) / 2;
        }
        return seq->get(midIndex);
    }

    void PrintStatistics(std::ostringstream& out, int startIndex, int endIndex)
    {
        if (endIndex - startIndex == 0) {
            throw std::runtime_error("Cannot print statistics of an empty subsequence.");
        }

        out << "Max element - " << Max(startIndex, endIndex) << "\n";
        out << "Min element - " << Min(startIndex, endIndex) << "\n";
        out << "Mean of set - " << Mean(startIndex, endIndex) << "\n";
        out << "Standard Deviation of set - " << StandardDeviation(startIndex, endIndex) << "\n";
        out << "Root Mean Square of set - " << RootMeanSquare(startIndex, endIndex) << "\n";
        out << "Median of set - " << Median(startIndex, endIndex) << "\n";
    }


};