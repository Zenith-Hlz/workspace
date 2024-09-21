#pragma once

#include <string>
#include <vector>
#include "Hash.h"

template <typename K, typename V>
class HashTable
{
private:
    struct HashEntry
    {
        K key;
        V value;
        bool isActive;

        HashEntry() : isActive(false) {}
        HashEntry(K k, V v) : key(k), value(v), isActive(true) {}
    };

    std::vector<HashEntry> table;
    Hash<K> hasher;

public:
    HashTable(int n) : hasher(n) { table.resize(n); }

    void addItem(const K &key, const V &value)
    {
        int index = hasher(key);
        table[index] = HashEntry(key, value);
    }

    void removeItem(const K &key)
    {
        int index = hasher(key);
        table[index].isActive = false; // Just mark as inactive instead of re-creating the entry
    }

    V *findByKey(const K &key)
    {
        int index = hasher(key);
        if (table[index].isActive)
        {
            return &(table[index].value);
        }
        else
        {
            return nullptr;
        }
    }
};
