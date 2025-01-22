#pragma once
#include "DynamicArray.hpp"
#include "Sequence.h"
#include "../pointers/SharedPtr.h"
#include <iostream>



    template <class T>
    class ArraySequence : public Sequence<T>
    {
    private:
        SharedPtr<DynamicArray<T>> dataArray;

    public:
        ArraySequence(T *items, int count)
        {
            this->dataArray = SharedPtr<DynamicArray<T>>(new DynamicArray<T>(items, count));
        }

        ArraySequence()
        {
            this->dataArray = SharedPtr<DynamicArray<T>>(new DynamicArray<T>());
        }

        ArraySequence(int size)
        {
            this->dataArray = SharedPtr<DynamicArray<T>>(new DynamicArray<T>(size));
        }

        ArraySequence(const ArraySequence<T> &array)
        {
            this->dataArray = array.dataArray;
        }

        // Returns the first element in the sequence
        const T& getFirst() const
        {
            return this->dataArray->get(0);
        }

        T& getFirst()
        {
            return this->dataArray->get(0);
        }

        // Returns the last element in the sequence
        const T& getLast() const
        {
            return this->dataArray->get(this->dataArray->getSize() - 1);
        }

        T& getLast()
        {
            return this->dataArray->get(this->dataArray->getSize() - 1);
        }

        // Returns the element at the specified index
        const T& get(int index) const
        {
            return this->dataArray->get(index);
        }

        T& get(int index)
        {
            return this->dataArray->get(index);
        }

        // Returns a subsequence from startIndex to endIndex
        UniquePtr<Sequence<T>> getSubsequence(int startIndex, int endIndex)
        {
            if (this->dataArray->getSize() <= 0 || startIndex < 0 || startIndex >= this->dataArray->getSize() ||
                endIndex < 0 || endIndex >= this->dataArray->getSize() || endIndex <= startIndex)
            {
                throw std::out_of_range("Incorrect index.");
            }
            else
            {
                auto subsequence = new ArraySequence<T>((endIndex - startIndex) + 1);
                int subIndex = 0;
                for (int i = startIndex; i <= endIndex; ++i)
                {
                    T element = this->dataArray->get(i);
                    subsequence->dataArray->set(subIndex++, element);
                }
                return UniquePtr<Sequence<T>>(subsequence);
            }
        }

        SharedPtr<Sequence<T>> copy(){
            UniquePtr<DynamicArray<T>> newArray = UniquePtr<DynamicArray<T>>();
            ArraySequence<T> *newSequence = new ArraySequence<T>();
            for (int i = 0; i < this->dataArray->getSize(); i++) {
                newSequence->append(this->dataArray->get(i));
            }
            return SharedPtr<Sequence<T>>(newSequence);
         }

        // Returns the length of the sequence
        int getLength() const
        {
            return this->dataArray->getSize();
        }

        void set(int index, T value) override
        {
            dataArray->set(index, value);
        }

        // Adds an element to the end of the sequence
        void append(T value) {
            dataArray->resize(getLength() + 1);
            dataArray->set(getLength() - 1, value);
        }

        // Adds an element to the start of the sequence
        void prepend(T item)
        {
            this->dataArray->resize(this->dataArray->getSize() + 1);
            for (int i = this->dataArray->getSize() - 1; i > 0; --i)
            {
                T element = this->dataArray->get(i - 1);
                this->dataArray->set(i, element);
            }
            this->dataArray->set(0, item);
        }

        // Inserts an element at the specified index
        void insertAt(T item, int index)
        {
            this->dataArray->resize(this->dataArray->getSize() + 1);
            for (int i = this->dataArray->getSize() - 1; i > index; --i)
            {
                T element = this->dataArray->get(i - 1);
                this->dataArray->set(i, element);
            }
            this->dataArray->set(index, item);
        }

        void remove(T item) {
            this->dataArray->remove(item);
        }

        // Concatenates this sequence with another ArraySequence
        UniquePtr<Sequence<T>> concat(Sequence<T> *sequence)
        {
            auto concatenatedSequence = new ArraySequence<T>(this->dataArray->getSize() + sequence->getLength());
            int concatIndex = 0;

            for (int i = 0; i < this->dataArray->getSize(); ++i)
            {
                concatenatedSequence->dataArray->set(concatIndex++, this->dataArray->get(i));
            }
            for (int i = 0; i < sequence->getLength(); ++i)
            {
                concatenatedSequence->set(concatIndex++, sequence->get(i));
            }

            return UniquePtr<Sequence<T>>(concatenatedSequence);
        }

        void swap(int index1, int index2) {
            auto temp = this->dataArray->get(index1);
            this->dataArray->set(index1, this->dataArray->get(index2));
            this->dataArray->set(index2, temp);
        }
    };

