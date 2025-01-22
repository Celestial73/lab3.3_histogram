#pragma once
template <typename T>
class SmartPtr
{
private:
    T *ptr;
    int *ref_count;

public:
    SmartPtr() : ptr(nullptr), ref_count(new int(0)) {}

    explicit SmartPtr(T *p) : ptr(p), ref_count(new int(1)) {}

    SmartPtr(const SmartPtr &other) : ptr(other.ptr), ref_count(other.ref_count)
    {
        ++(*ref_count);
    }

    SmartPtr &operator=(const SmartPtr &other)
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    SmartPtr(SmartPtr &&other) noexcept : ptr(other.ptr), ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    SmartPtr &operator=(SmartPtr &&other) noexcept
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    ~SmartPtr()
    {
        release();
    }

    T &operator*() const
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

    void reset(T *p = nullptr)
    {
        release();
        if (p)
        {
            ptr = p;
            ref_count = new int(1);
        }
    }

    int num_count() const
    {
        return *ref_count;
    }

private:
    void release()
    {
        if (ref_count)
        {
            --(*ref_count);
            if (*ref_count <= 0)
            {
                delete ptr;
                delete ref_count;
            }
        }
        ptr = nullptr;
        ref_count = nullptr;
    }
    void checkIsEmpty()
    {
        if (ptr == nullptr)
            throw std::out_of_range("Accessing empty SmartPointer.");
    }
};