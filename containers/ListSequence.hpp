#pragma once
#include <iostream>
#include "LinkedList.hpp"
#include "Sequence.h"
#include "../pointers/UniquePtr.h" // Include UniquePtr for memory management

template <class T>
class ListSequence : public Sequence<T>
{
private:
    UniquePtr<LinkedList<T>> listData; // UniquePtr to manage LinkedList

public:
    // Constructor with array of items
    ListSequence(T *items, int count)
    {
        this->listData = UniquePtr<LinkedList<T>>(new LinkedList<T>(items, count));
    }

    // Default constructor
    ListSequence()
    {
        this->listData = UniquePtr<LinkedList<T>>(new LinkedList<T>());
    }

    // Copy constructor
    ListSequence(const ListSequence &other)
    {
        listData = UniquePtr<LinkedList<T>>(new LinkedList<T>(*other.listData));
    }

    // Move constructor
    ListSequence(ListSequence<T> &&list) noexcept
    {
        this->listData = std::move(list.listData); // Transfer ownership of pointer
    }

    // Copy assignment operator
    ListSequence &operator=(const ListSequence &other)
    {
        if (this != &other)
        {
            if (other.listData.get() != nullptr)
            {
                listData = UniquePtr<LinkedList<T>>(new LinkedList<T>(*other.listData));
            }
        }
        return *this;
    }

    // Move assignment operator
    ListSequence<T> &operator=(ListSequence<T> &&list) noexcept
    {
        if (this != &list)
        {
            this->listData = std::move(list.listData); // Transfer ownership
        }
        return *this;
    }

    // Get the first element
    const T &getFirst() const
    {
        return this->listData->getFirst();
    }

    // Get the last element
    const T &getLast() const
    {
        return this->listData->getLast();
    }

    // Get an element by index
    const T &get(int index) const
    {
        return this->listData->get(index);
    }

    // Get an element by index
    T &get(int index)
    {
        return this->listData->get(index);
    }

    void set(int index, T value)
    {
        if (index < 0 || index >= listData->getLength())
        {
            throw std::out_of_range("Index out of range");
        }
        listData->set(index, value);
    }

    // Get a subsequence as a new ListSequence
    UniquePtr<Sequence<T>> getSubsequence(int startIndex, int endIndex)
    {
        UniquePtr<LinkedList<T>> sublist = UniquePtr<LinkedList<T>>(this->listData->getSubList(startIndex, endIndex));
        ListSequence<T> *newSequence = new ListSequence<T>();
        newSequence->listData = std::move(sublist); // Transfer ownership of pointer
        return UniquePtr<Sequence<T>>(newSequence);
    }

    SharedPtr<Sequence<T>> copy()
    {
        UniquePtr<LinkedList<T>> newList = UniquePtr<LinkedList<T>>(this->listData->copy());
        ListSequence<T> *newSequence = new ListSequence<T>();
        newSequence->listData = std::move(newList); // Transfer ownership of pointer
        return SharedPtr<Sequence<T>>(newSequence);
    }

    // Get the length of the sequence
    int getLength() const
    {
        return this->listData->getLength();
    }

    // Append an item to the end of the sequence
    void append(T item)
    {
        this->listData->append(item);
    }

    void swap(int index1, int index2) override
    {
        T temp1 = listData->get(index1);
        T temp2 = listData->get(index2);

        listData->set(index2, temp1);
        listData->set(index1, temp2);
    }

    // Prepend an item to the beginning of the sequence
    void prepend(T item)
    {
        this->listData->prepend(item);
    }

    // Insert an item at a specified index
    void insertAt(T item, int index)
    {
        this->listData->insertAt(item, index);
    }

    // Remove an item at a specific index
    void removeAt(int index)
    {
        this->listData->removeAt(index);
    }

    // Concatenate two sequences
    UniquePtr<Sequence<T>> concat(Sequence<T> *other)
    {
        UniquePtr<Sequence<T>> result(new ListSequence<T>());
        for (int i = 0; i < getLength(); ++i)
        {
            result->append(get(i));
        }
        for (int i = 0; i < other->getLength(); ++i)
        {
            result->append(other->get(i));
        }
        return result;
    }
};
