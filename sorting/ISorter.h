#pragma once

#include <functional>
#include "../containers/Sequence.h"
#include "../pointers/SharedPtr.h"

template <class T>
class ISorter
{
public:
    virtual ~ISorter() = default;

    virtual void sort(SharedPtr<Sequence<T>> sequence,
                      std::function<bool(const T &, const T &)> compare) = 0;
};
