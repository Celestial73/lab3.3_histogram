#pragma once

#include "IDictionaryIteraror.h"
#include "../pointers/UniquePtr.h"
template <typename Tkey, typename TElement>

class IDictionary
{
public:
	virtual int GetCount() const = 0;
	virtual int GetCapacity() const = 0;
	virtual TElement Get(const Tkey &key) const = 0;
	virtual bool ContainsKey(const Tkey &key) const = 0;
	virtual void Add(const Tkey &key, const TElement &element) = 0;
	virtual void Remove(const Tkey &key) = 0;
	virtual void Update(const Tkey &key, const TElement &element) = 0;
	virtual ~IDictionary() = default;
	virtual UniquePtr<IDictionaryIterator<Tkey, TElement>> GetIterator() const = 0;
};