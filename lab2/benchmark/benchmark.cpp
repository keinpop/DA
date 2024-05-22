#include "../patricia/Patricia.h"

#include <vector>
#include <string>
#include <chrono>

void LowercaseConverter(char* str)
{
    for (size_t i = 0; i < strlen(str); ++i) {
        str[i] = str[i] >= 'A' && str[i] <= 'Z' ? str[i] - 'A' + 'a' : str[i];
    }
}

int main()
{
    srand(time(nullptr));

    TPatricia test_1;
    std::vector<char* > vec_1;
    size_t lengthWord = 10000000; 
    size_t sizeTrie = 10;
    for (int i = 0; i < sizeTrie; ++i) {
        char* tmp = new char[lengthWord];
        for (int j = 0; j < lengthWord; ++j) {
            tmp[j] = (rand() % 26) + 'a';
        }
        vec_1.push_back(tmp);
    }

    std::cout << "TEST 1 - Insert\t SIZE: " << lengthWord << '\n';
    auto start1 = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < sizeTrie; ++i) {
        test_1.Insert(vec_1[i], i);
    }

    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

    std::cout << "TEST 2 - Find\t SIZE: " << lengthWord << '\n';
    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < sizeTrie; ++i) {
        test_1.Find(vec_1[i]); 
    }

    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);

    std::cout << "DONE!\n";
    std::cout << "Time to insert: " << duration1.count() << '\n';
    std::cout << "Time to find: " << duration2.count() << '\n';

    for (int i = 0; i < sizeTrie; ++i) {
        delete[] vec_1[i];
    }

    return 0;
}