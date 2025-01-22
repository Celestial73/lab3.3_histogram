#pragma once
#include <iostream>
#include <utility>
#include "../pointers/UniquePtr.h"


    template <class T>
    class DynamicArray
    {
    private:
        UniquePtr<T[]> elements;
        int size;

    public:
        // Constructs the array with elements from an existing array of items
        DynamicArray(T *items, int itemCount)
        {
            checkNewSize(itemCount);
            this->elements = UniquePtr<T[]>(new T[itemCount]);
            this->size = itemCount;
            std::copy(items, items + itemCount, elements.get());
        }

        // Default constructor creates an empty array
        DynamicArray()
        {
            this->elements = UniquePtr<T[]>();
            this->size = 0;
        }

        // Constructs an array with a specified size
        DynamicArray(int newSize)
        {
            checkNewSize(newSize);
            this->size = newSize;
            this->elements = UniquePtr<T[]>(new T[newSize]);
        }

        // Copy constructor for creating a copy of another DynamicArray
        DynamicArray(DynamicArray<T> &otherArray)
        {
            this->size = otherArray.size;
            this->elements = UniquePtr(new T[this->size]);
            for (int i = 0; i < this->size; i++)
            {
                *(this->elements.get(i)) = *(otherArray.elements.get(i));
            }
        }

        // Returns the element at the specified index
        const T& get(int index) const
        {
            if (index < 0 || index >= size)
                throw std::out_of_range("index");
            return elements[index];
        }

        T& get(int index)
        {
            if (index < 0 || index >= size)
                throw std::out_of_range("index");
            return elements[index];
        }

        // Returns the size of the array
        int getSize() const
        {
            return this->size;
        }

        // Sets the element at the specified index to a new value
        void set(int index, T value)
        {
            if (index < 0 || index >= size)
            {
                throw std::out_of_range("index");
            }
            elements[index] = value;
        }

        // Resizes the array to a new size
        void resize(int newSize)
        {
            if (newSize < 0)
            {
                throw std::out_of_range("wrong newSize input");
            }
            if (newSize == 0)
            {
                this->size = 0;
                this->elements = UniquePtr<T[]>();
                return;
            }
            UniquePtr<T[]> newData(new T[newSize]);
            int elemSize = std::min(size, newSize);
            std::copy(elements.get(), elements.get() + elemSize, newData.get());
            elements = std::move(newData);
            this->size = newSize;
        }


        void remove(T element)
        {
            size_t count = 0;
            for (size_t i = 0; i < this->size; i++)
            {
                if (is_equal(this->elements[i],  element))
                {
                    count++;
                }
            }
            if (count == 0)
            {
                return;
            }
            T* new_arr = new T[this->size - count];
            size_t j = 0;
            for (size_t i = 0; i < this->size; i++) {
                if (!is_equal(this->elements[i] , element))
                {
                    new_arr[j] = this->elements[i];
                    j++;
                }
            }
            this->size -= count;
            elements = new_arr;
        }


    private:
        void checkNewSize(int size)
        {
            if (size < 1)
            {
                throw std::invalid_argument("Invalid array size");
            }
        }
    };
