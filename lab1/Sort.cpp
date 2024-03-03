#include "./Sort.h"

void CountingSortByte(TVector<TSortType*> & arr, int exp)
{
    const int SIZE = arr.GetSize();
    const size_t MAX_VALUE_DIGIT_BYTE = 256;
    const int BIT_MASK = 0xFF;

    TVector<TSortType*> output(SIZE);
    
    TVector<int> count(MAX_VALUE_DIGIT_BYTE, 0);

    for (int i = 0; i < SIZE; ++i) {
        ++count[(arr[i]->Key.Days >> exp) & BIT_MASK];
    }

    for (int i = 1; i < MAX_VALUE_DIGIT_BYTE; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = SIZE - 1; i >= 0; --i) {
        output[count[(arr[i]->Key.Days >> exp) & BIT_MASK] - 1] = arr[i];
        --count[(arr[i]->Key.Days >> exp) & BIT_MASK];
    }

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = output[i];
    }
}

uint64_t FindMaxElement(const TVector<TSortType*> & arr) 
{
    unsigned long long maxELem = arr[0]->Key.Days; 
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        if (maxELem < arr[i]->Key.Days) {
            maxELem = arr[i]->Key.Days;
        }
    }

    return maxELem;
}

void RadixSort(TVector<TSortType*> & arr) 
{
    unsigned long long maxElement = FindMaxElement(arr);
    const int NUMBER_OF_BITS_PER_DIGIT = 8;
    for (int exp = 0; maxElement >> exp > 0; exp += NUMBER_OF_BITS_PER_DIGIT) {
        CountingSortByte(arr, exp);
    }
}

void PrintArrayTSortType(const TVector<TSortType*> & arr)
{
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        for (size_t j = 0; j < arr[i]->Key.Data.GetSize(); ++j) {
            std::cout << arr[i]->Key.Data[j];
        }
        std::cout << '\t' << arr[i]->Value << '\n';
    }
}