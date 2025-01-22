#pragma once
template <typename T>
class SharedPtr
{

public:
    SharedPtr() : ptr(nullptr), ref_count(nullptr) {}

    explicit SharedPtr(T *p) : ptr(p), ref_count(new int(1)) {}

    SharedPtr(const SharedPtr &other) : ptr(other.ptr), ref_count(other.ref_count)
    {
        if (ref_count)
        {
            ++(*ref_count);
        }
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            if (ptr == nullptr)
                return *this; // if the other pointer is nullptr,
                              // make this one null and keep the ref_count nullptr
            ref_count = other.ref_count;
            if (ref_count)
            {
                ++(*ref_count);
            }
        }
        return *this;
    }

    ~SharedPtr()
    {
        release();
    }

    int num_count() const
    {
        return ref_count ? *ref_count : 0;
    }

    T &operator*()
    {
        checkIsEmpty();
        return *ptr;
    }

    const T &operator*() const
    {
        checkIsEmpty();
        return *ptr;
    }

    const T *operator->() const
    {
        return ptr;
    }

    T *operator->()
    {
        return ptr;
    }

    T *get() const
    {
        return ptr;
    }

    void reset(T *p = nullptr)
    {
        release();
        if (p)
        {
            ptr = p;
            ref_count = new int(1);
        }
        else
        {
            ptr = nullptr;
            ref_count = nullptr;
        }
    }

private:
    T *ptr;
    int *ref_count;

    void release()
    {
        if (ref_count)
        {
            --(*ref_count);
            if (*ref_count <= 0)
            {
                delete ptr;
                delete ref_count;
                ptr = nullptr;
                ref_count = nullptr;
            }
        }
    }

    void checkIsEmpty()
    {
        if (ptr == nullptr)
            throw std::out_of_range("Accessing empty SmartPointer.");
    }
};
