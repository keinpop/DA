#include <iostream>
#include <vector>

typedef int TCountSort;

void countingSort(TCountSort* array, size_t s)
{
    TCountSort maxValInArr = 0;
    for (int i = 0; i < s; ++i) {
        if (array[i] > maxValInArr) {
            maxValInArr = array[i];
        }
    }

    std::vector<TCountSort> countingArray(maxValInArr + 1, 0);

    for (int i = 0; i < s; ++i) {
        ++countingArray[array[i]];
    }


    int i = 0, j = 0; // i - countingArray; j - input array
    while (i != s + 1) {
        if (countingArray[i] > 0) {
            array[j] = i;
            ++j;
            --countingArray[i];
            continue;
        }
        ++i;
    }
}

int main()
{
    size_t size = 6;
    TCountSort arr[size] = {1, 6, 4, 0, 3, 5};

    std::cout << "Array before sorting\n";
    for (auto & x : arr) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    countingSort(arr, size);

    std::cout << "Array after sorting\n";
    for (auto & x : arr) {
        std::cout << x << ' ';
    }
    
    std::cout << std::endl;

    return 0;
}