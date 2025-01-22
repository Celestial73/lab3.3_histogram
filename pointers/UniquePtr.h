#pragma once
#include <stdexcept>

template <typename T>
class UniquePtr
{
private:
    T *ptr;

public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T *ptr) : ptr(ptr) {}

    ~UniquePtr()
    {
        delete ptr;
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T &operator*()
    {
        return *ptr;
    }

    const T &operator*() const
    {
        return *ptr;
    }

    T *operator->()
    {
        return ptr;
    }

    const T *operator->() const
    {
        return ptr;
    }

    const T *get() const
    {
        return ptr;
    }

    T *get()
    {
        return ptr;
    }

    T *release()
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T *newPtr = nullptr)
    {
        delete ptr;
        ptr = newPtr;
    }

private:
    void checkIsEmpty()
    {
        if (ptr == nullptr)
            throw std::out_of_range("Accessing empty SmartPointer.");
    }
};

template <typename T>
class UniquePtr<T[]>
{
private:
    T *ptr;

public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T *ptr) : ptr(ptr) {}

    ~UniquePtr()
    {
        delete[] ptr;
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T &operator[](std::size_t index)
    {
        if (!ptr)
            throw std::runtime_error("Empty pointer");
        return ptr[index];
    }

    const T &operator[](std::size_t index) const
    {
        if (!ptr)
            throw std::runtime_error("Empty pointer");
        return ptr[index];
    }

    T &operator*()
    {
        return *ptr;
    }

    const T &operator*() const
    {
        return *ptr;
    }

    T *operator->()
    {
        return ptr;
    }

    const T *operator->() const
    {
        return ptr;
    }

    const T *get() const
    {
        return ptr;
    }

    T *get()
    {
        return ptr;
    }

    T *release()
    {
        T *temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T *newPtr = nullptr)
    {
        if (ptr)
            delete[] ptr;
        ptr = newPtr;
    }

private:
    void checkIsEmpty()
    {
        if (ptr == nullptr)
            throw std::out_of_range("Accessing empty SmartPointer.");
    }
};
