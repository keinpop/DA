#include <algorithm>
#include <chrono>

#include "../Vector.h"

void CountingSortByteInt(TVector<uint64_t*> & arr, int exp)
{
    const int SIZE = arr.GetSize();
    const size_t MAX_VALUE_DIGIT_BYTE = 256;
    const int BIT_MASK = 0xFF;

    TVector<uint64_t*> output(SIZE);
    
    TVector<int> count(MAX_VALUE_DIGIT_BYTE, 0);

    for (int i = 0; i < SIZE; ++i) {
        ++count[(*arr[i] >> exp) & BIT_MASK];
    }

    for (int i = 1; i < MAX_VALUE_DIGIT_BYTE; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = SIZE - 1; i >= 0; --i) {
        output[count[(*arr[i] >> exp) & BIT_MASK] - 1] = arr[i];
        --count[(*arr[i] >> exp) & BIT_MASK];
    }

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = output[i];
    }
}

uint64_t FindMaxElementInt(const TVector<uint64_t*> & arr) 
{
    uint64_t maxELem = *arr[0];
    for (size_t i = 0; i < arr.GetSize(); ++i) {
        if (maxELem < *arr[i]) {
            maxELem = *arr[i];
        }
    }
    return maxELem;
}

void RadixSortInt(TVector<uint64_t*> & arr) 
{
    uint64_t maxElement = FindMaxElementInt(arr);
    const int NUMBER_OF_BITS_PER_DIGIT = 8;
    for (int exp = 0; maxElement >> exp > 0; exp += NUMBER_OF_BITS_PER_DIGIT) {
        CountingSortByteInt(arr, exp);
    }
}


int main()
{
    srand(time(NULL));
    size_t size1 = 1000, size2 = 5000, size3 = 10000, size4 = 15000;
    
    TVector<uint64_t> testArr1(size1);
    TVector<uint64_t*> testArr1ToMySort(size1);
    for (int i = 0; i < size1; ++i) {
        testArr1[i] = rand();
        uint64_t* tmp = new uint64_t;
        *tmp = rand();
        testArr1ToMySort[i] = tmp;
    }

    TVector<uint64_t> testArr2(size2);
    TVector<uint64_t*> testArr2ToMySort(size2);
    for (size_t i = 0; i < size2; ++i) {
        testArr2[i] = rand();
        uint64_t* tmp = new uint64_t;
        *tmp = rand();
        testArr2ToMySort[i] = tmp;
    }

    TVector<uint64_t> testArr3(size3);
    TVector<uint64_t*> testArr3ToMySort(size3);
    for (size_t i = 0; i < size3; ++i) {
        testArr3[i] = rand();
        uint64_t* tmp = new uint64_t;
        *tmp = rand();
        testArr3ToMySort[i] = tmp;
    }

    TVector<uint64_t> testArr4(size4);
    TVector<uint64_t*> testArr4ToMySort(size4);
    for (size_t i = 0; i < size4; ++i) {
        testArr4[i] = rand();
        uint64_t* tmp = new uint64_t;
        *tmp = rand();
        testArr4ToMySort[i] = tmp;
    }

    std::cout << "TEST 1\t SIZE: 1000\n";
    auto start1 = std::chrono::high_resolution_clock::now();
    std::sort(testArr1.begin(), testArr1.end());
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

    auto start1ToMyArr = std::chrono::high_resolution_clock::now();
    RadixSortInt(testArr1ToMySort);
    auto stop1ToMyArr = std::chrono::high_resolution_clock::now();
    auto duration1ToMyArr = std::chrono::
        duration_cast<std::chrono::microseconds>(stop1ToMyArr - start1ToMyArr);
    
    std::cout << "|MY| RadixSort : " << duration1ToMyArr.count() << " microseconds\n";
    std::cout << "|STD| sort : " << duration1.count() << " microseconds\n";
    
    //delete
    for (int i = 0; i < size1; ++i) {
        delete testArr1ToMySort[i];
    }

    //##########################
    std::cout << "\nTEST 2\t SIZE: 5000\n";
    auto start2 = std::chrono::high_resolution_clock::now();
    std::sort(testArr2.begin(), testArr2.end());
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    auto start2ToMyArr = std::chrono::high_resolution_clock::now();
    RadixSortInt(testArr2ToMySort);
    auto stop2ToMyArr = std::chrono::high_resolution_clock::now();
    auto duration2ToMyArr = std::chrono::
        duration_cast<std::chrono::microseconds>(stop2ToMyArr - start2ToMyArr);
    
    std::cout << "|MY| RadixSort : " << duration2ToMyArr.count() << " microseconds\n";
    std::cout << "|STD| sort : " << duration2.count() << " microseconds\n";

    for (int i = 0; i < size2; ++i) {
        delete testArr2ToMySort[i];
    }
    
    //##########################
    std::cout << "\nTEST 3\t SIZE: 10000\n";
    auto start3 = std::chrono::high_resolution_clock::now();
    std::sort(testArr3.begin(), testArr3.end());
    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);

    auto start3ToMyArr = std::chrono::high_resolution_clock::now();
    RadixSortInt(testArr3ToMySort);
    auto stop3ToMyArr = std::chrono::high_resolution_clock::now();
    auto duration3ToMyArr = std::chrono::
        duration_cast<std::chrono::microseconds>(stop3ToMyArr - start3ToMyArr);
    
    std::cout << "|MY| RadixSort : " << duration3ToMyArr.count() << " microseconds\n";
    std::cout << "|STD| sort : " << duration3.count() << " microseconds\n";

    for (int i = 0; i < size3; ++i) {
        delete testArr3ToMySort[i];
    }

    //##########################
    std::cout << "\nTEST 4\t SIZE: 15000\n";
    auto start4 = std::chrono::high_resolution_clock::now();
    std::sort(testArr4.begin(), testArr4.end());
    auto stop4 = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(stop4 - start4);

    auto start4ToMyArr = std::chrono::high_resolution_clock::now();
    RadixSortInt(testArr4ToMySort);
    auto stop4ToMyArr = std::chrono::high_resolution_clock::now();
    auto duration4ToMyArr = std::chrono::
        duration_cast<std::chrono::microseconds>(stop4ToMyArr - start4ToMyArr);
    
    std::cout << "|MY| RadixSort : " << duration4ToMyArr.count() << " microseconds\n";
    std::cout << "|STD| sort : " << duration4.count() << " microseconds\n";
    
    for (int i = 0; i < size4; ++i) {
        delete testArr4ToMySort[i];
    }

    return 0;
}