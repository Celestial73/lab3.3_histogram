#pragma once

#include "../pointers/UniquePtr.h"
#include "../pointers/SharedPtr.h"


    template <class T>
    class Sequence
    {
    public:
        virtual const T &getFirst() const = 0;
        virtual const T &getLast() const = 0;
        virtual const T &get(int index) const = 0;
        virtual int getLength() const = 0;
        virtual void append(T item) = 0;
        virtual void insertAt(T item, int index) = 0;
        virtual void set(int index1, T value) = 0;
        virtual void swap(int index1, int index2) = 0;
        virtual UniquePtr<Sequence<T>> concat(Sequence<T> *Sequence) = 0;
        virtual SharedPtr<Sequence<T>> copy() = 0;
        virtual UniquePtr<Sequence<T>> getSubsequence(int startIndex, int endIndex) = 0;
    };
