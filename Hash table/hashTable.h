//
//  File.h
//  Hash table
//
//  Created by Андрей Рычков on 17.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef __Hash_table__File__
#define __Hash_table__File__

#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include "List.h"

struct hasher
{
    int operator () (int x)
    {
        int hash = 17;
        while (x != 0)
        {
            hash = (1261 * hash + (x % 10)) % 65537;
            x /= 10;
        }
        return hash;
    }
};

template <class keyType, class valueType, class hasher>
class hash_Table
{
    struct node
    {
        int hash;
        List<std::pair<keyType, valueType>> table;
        node (): hash(0) {}
        node (const keyType& key)
        {
            hasher Hasher;
            hash = Hasher(key);
        }
        bool operator < (const node& other) const
        {
            return (hash < other.hash);
        }
        bool operator == (const node& other) const
        {
            return (hash == other.hash);
        }
    };
    unsigned int count;
    List<node> _pairs;
public:
    typename List<std::pair<keyType, valueType>>::iterator end()
    {
        return typename List<std::pair<keyType, valueType>>::iterator(NULL);
    }
    hash_Table (): count(0) { }
    void print()
    {
        typename List<node>::iterator pos;
        typename List<std::pair<keyType, valueType>>::iterator pos1;
        for (pos = _pairs.begin(); pos != _pairs.end(); ++pos)
        {
            for (pos1 = (*pos).table.begin(); pos1 != (*pos).table.end(); ++pos1)
            {
                std::cout << (*pos1).first << ": " << (*pos1).second << std::endl;
            }
        }
        std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    }
    void insert (const keyType& key, const valueType& value)
    {
        node toInsert(key);
        typename List<node>::iterator pos = _pairs.find(toInsert);
        if (pos == _pairs.end())
        {
            _pairs.push_back(toInsert);
            _pairs[_pairs.size()-1].table.push_back(std::make_pair(key, value));
        }
        else
        {
            (*pos).table.push_back(std::make_pair(key, value));
        }
        _pairs.sort();
        ++count;
    }
    void erase (const keyType& key)
    {
        node toErase(key);
        typename List<node>::iterator pos = _pairs.find(toErase);
        typename List<std::pair<keyType, valueType>>::iterator now;
        if (pos != _pairs.end())
        {
            for (now = (*pos).table.begin(); now != (*pos).table.end(); ++now)
            {
                if ((*now).first == key)
                {
                    (*pos).table.erase(std::make_pair(key, (*now).second));
                }
                if ((*pos).table.empty())
                {
                    _pairs.erase(*pos);
                    return;
                }
            }
        }
        --count;
    }
    const typename List<std::pair<keyType,valueType>>::iterator find (const keyType& key)
    {
        node toFind(key);
        typename List<node>::iterator pos = _pairs.find(toFind);
        typename List<std::pair<keyType, valueType>>::iterator now;
        if (pos != _pairs.end())
        {
            for (now = (*pos).table.begin(); now != (*pos).table.end(); ++now)
            {
                if ((*now).first == key)
                {
                    return now;
                }
            }
            return end();
        }
        return end();
    }
};

#endif /* defined(__Hash_table__File__) */
