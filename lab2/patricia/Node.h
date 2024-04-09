#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

typedef uint64_t TValue;
typedef char TKey;

struct TNode
{
    void Init(const int & b, TKey* k, const TValue & val, TNode* l, TNode* r)
    {
        this->Bit = b;
        if (k) {
            Key = new TKey[strlen(k) + 1];
            strcpy(Key, k);
        } else {
            Key = k;
        }

        Value = val;
        Left = l;
        Right = r;
    }

    TNode()
    {
        // We set two pointer to 'this' because is a backlink
        Init(-1, 0, 0, this, this);
    }

    TNode(const int & b, TKey* k, const TValue & val) 
    {
        Init(b, k, val, this, this);
    }

    TNode(const int & b, TKey* k, const TValue & val, TNode* l, TNode* r)
    {
        Init(b, k, val, l, r);
    }

    ~TNode()
    {
        delete[] Key;
    }

    int PosOfDiffBit = -1;
    int Bit;

    TKey* Key;
    TValue Value;

    TNode* Left;
    TNode* Right;
};
