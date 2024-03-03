#pragma once

#include "./Vector.h"

struct TData {
    TVector<char> Data;
    uint64_t Days;
};  

struct TSortType {
    TData Key;
    uint64_t Value;
};

uint64_t FindMaxElement(const TVector<TSortType*> & arr);

void CountingSortByte(TVector<TSortType*> & arr, int exp);
void RadixSort(TVector<TSortType*> & arr);

void PrintArrayTSortType(const TVector<TSortType*> & arr);