#pragma once


#include "ArraySequence.hpp"
#include "IDictionary.h"
#include "ListSequence.hpp"
#include "IDictionaryIteraror.h"
#include <iostream>
#include <functional>
#include <stdexcept>
#include <type_traits>
#include "IndexPair.h"

template <typename Tkey, typename TElement>
class HashTable
{
private:
    struct Pair
    {
        Tkey key;
        TElement element;

        Pair() : key(), element() {}

        Pair(const Tkey &k, const TElement &elem) : key(k), element(elem) {}

        Pair(const Pair &other) : key(other.key), element(other.element) {}

        Pair &operator=(const Pair &other)
        {
            if (this != &other)
            {
                key = other.key;
                element = other.element;
            }
            return *this;
        }

        Pair(Pair &&other) noexcept : key(std::move(other.key)), element(std::move(other.element)) {}

        Pair &operator=(Pair &&other) noexcept
        {
            if (this != &other)
            {
                key = std::move(other.key);
                element = std::move(other.element);
            }
            return *this;
        }
    };

    UniquePtr<ArraySequence<ListSequence<Pair>>> table;
    int count;
    int capacity;

    size_t hashFunction(const Tkey &key) const
    {
        if constexpr (std::is_same<Tkey, IndexPair>::value)
        {
            return IndexPairHash()(key);
        }
        else
        {
            return std::hash<Tkey>()(key);
        }
    }

    void rehash()
    {
        // Double the capacity
        int new_capacity = capacity * 2;

        // Create a new table with the updated capacity
        UniquePtr<ArraySequence<ListSequence<Pair>>> new_table(new ArraySequence<ListSequence<Pair>>(new_capacity));
        for (int i = 0; i < new_capacity; i++)
        {
            new_table->append(ListSequence<Pair>());
        }

        // Rehash existing elements
        for (int i = 0; i < capacity; i++)
        {
            // Get the chain (bucket) at the current index in the old table
            ListSequence<Pair> &chain = table->get(i);

            // Move each element to the new table based on the new hash index
            for (int j = 0; j < chain.getLength(); ++j)
            {
                Pair &p = chain.get(j);

                // Recalculate the index based on the new capacity
                int index = hashFunction(p.key) % new_capacity;

                // Append the pair to the new chain
                new_table->get(index).append(std::move(p));
            }
        }

        // Update the table to the new one
        table = std::move(new_table);
        capacity = new_capacity; // Update the capacity to the new size
    }

public:
    explicit HashTable(const int c = 13) : count(0), capacity(c)
    {
        table = UniquePtr(new ArraySequence<ListSequence<Pair>>(c)); // Initialize table
        for (int i = 0; i < capacity; i++)
        {
            table->append(ListSequence<Pair>());
        }
    }

    int getCount() const
    {
        return count;
    }

    int getCapacity() const
    {
        return capacity;
    }

    TElement get(const Tkey &key) const
    {
        int index = hashFunction(key) % capacity;
        const ListSequence<Pair> &chain = table->get(index);
        for (int i = 0; i < chain.getLength(); i++)
        {
            if (chain.get(i).key == key)
            {
                return chain.get(i).element;
            }
        }
        throw std::runtime_error("Key not in Table");
    }

    bool containsKey(const Tkey &key) const
    {
        int index = hashFunction(key) % capacity;
        const ListSequence<Pair> &chain = table->get(index);
        for (int i = 0; i < chain.getLength(); i++)
        {
            if (chain.get(i).key == key)
            {
                return true;
            }
        }
        return false;
    }

    void add(const Tkey &key, const TElement &elem)
    {
        int index = hashFunction(key) % capacity;
        ListSequence<Pair> &chain = table->get(index);

        // Check if the key already exists, and update its value if so
        for (int i = 0; i < chain.getLength(); i++)
        {
            if (chain.get(i).key == key)
            {
                chain.get(i).element = elem;
                return;
            }
        }

        // If the key doesn't exist, add a new pair
        chain.append(Pair(key, elem));
        count++;

        // Check if rehashing is needed (when count exceeds capacity)
        if (count >= capacity)
        {
            rehash();
        }
    }

    void update(const Tkey &key, const TElement &element)
    {
        size_t index = hashFunction(key) % capacity;
        ListSequence<Pair> &chain = table->get(static_cast<int>(index));

        for (int i = 0; i < chain.getLength(); ++i)
        {
            if (chain.get(i).key == key)
            {
                chain.get(i).element = element;
                return;
            }
        }

        throw std::runtime_error("Key not found.");
    }
    void remove(const Tkey &key)
    {
        int index = hashFunction(key) % capacity;
        ListSequence<Pair> &chain = table->get(index);
        for (int i = 0; i < chain.getLength(); i++)
        {
            if (chain.get(i).key == key)
            {
                chain.removeAt(i);
                --count;
                return;
            }
        }
        throw std::runtime_error("Key not in table.");
    }

    ~HashTable() = default;

    class HashTableIterator
    {
    public:
        HashTableIterator(const HashTable *hashTable) : hashTable(hashTable), bucketIndex(0), listIndex(-1) {}

        ~HashTableIterator() = default;

        bool moveNext()
        {
            ++listIndex;
            while (bucketIndex < hashTable->capacity)
            {
                const ListSequence<Pair> &chain = hashTable->table->get(static_cast<int>(bucketIndex));
                if (listIndex < chain.getLength())
                {
                    return true;
                }
                else
                {
                    ++bucketIndex;
                    listIndex = 0;
                }
            }
            return false;
        }

        void reset()
        {
            bucketIndex = 0;
            listIndex = -1;
        }

        Tkey getCurrentKey() const
        {
            if (bucketIndex >= hashTable->capacity)
                throw std::out_of_range("Iterator out of range");

            const ListSequence<Pair> &chain = hashTable->table->get(static_cast<int>(bucketIndex));
            return chain.get(listIndex).key;
        }

        TElement getCurrentValue() const
        {
            if (bucketIndex >= hashTable->capacity)
                throw std::out_of_range("Iterator out of range");

            const ListSequence<Pair> &chain = hashTable->table->get(static_cast<int>(bucketIndex));
            return chain.get(listIndex).element;
        }

    private:
        const HashTable *hashTable;
        size_t bucketIndex;
        int listIndex;
    };

    UniquePtr<HashTableIterator> getIterator() const
    {
        return UniquePtr<HashTableIterator>(new HashTableIterator(this));
    }
};

