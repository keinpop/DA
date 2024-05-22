#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <chrono>

void createZArr(const std::string & str, int Z[])
{
    size_t n = str.size();
    /* 
        L - левая граница покрытия, R - правая
        граница покрытия, k - промежуточное 
        значение для посчета расстояния проверки
        вышли ли мы за границы
    */
    int L, R, k;

    L = R = 0;
    for (size_t i = 1; i < n; ++i) {
        if (i > R) {
            L = R = i;

            while (R < n && str[R - L] == str[R]) {
                ++R;
            }

            Z[i] = R - L;
            --R;

        } else {
            k = i - L;

            if (Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } else {
                L = i;

                while (R < n && str[R - L] == str[R]) {
                    R++;
                }

                Z[i] = R - L;
                --R;
            }

        }
    }

}

/*
    Маленькая функция для форматирования строки:
    т.к. на вход на могут передать "кривую строку",
    то мы должны ее "нормализовать", то есть сделать ее 
    без лишних пробелов, 
*/
void removeExtraSpace(std::string & str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [] (char c) {
        return !std::isspace(c);
    }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [] (char c) {
        return !std::isspace(c);
    }).base(), str.end());

    auto spaceEnd = std::unique(str.begin(), str.end(), [] (char a, char b) {
        return std::isspace(a) && std::isspace(b);
    });

    str.erase(spaceEnd, str.end());
}

int main()
{   
    srand(time(nullptr));

    std::string strTest1; //10.000
    size_t strSizeTest1 = 10000;
    size_t patternSize1 = 10;
    std::string tmp;
    for (size_t i = 0; i < strSizeTest1; ++i) {
        if (i == patternSize1) {
            tmp = '$';
            strTest1.append(tmp);
            continue;
        }

        if (rand() % 15 == 0) {
            tmp = ' ';
        } else {
            tmp = (rand() % 26) + 'a';
        }

        strTest1.append(tmp);
    }

    std::cout << "TEST 1 - \t SIZE: " << strSizeTest1 << '\n';
    auto start1 = std::chrono::high_resolution_clock::now();

    int Z1[strSizeTest1];
    createZArr(strTest1, Z1);
    
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

    //-------------------------------------------

    std::string strTest2; //1.000.000
    size_t strSizeTest2 = 1000000;
    size_t patternSize2 = 100;
    // std::string tmp;
    for (size_t i = 0; i < strSizeTest2; ++i) {
        if (i == patternSize2) {
            tmp = '$';
            strTest2.append(tmp);
            continue;
        }

        if (rand() % 15 == 0) {
            tmp = ' ';
        } else {
            tmp = (rand() % 26) + 'a';
        }

        strTest2.append(tmp);
    }

    std::cout << "TEST 2 - \t SIZE: " << strSizeTest2 << '\n';
    auto start2 = std::chrono::high_resolution_clock::now();

    int Z2[strSizeTest2];
    createZArr(strTest2, Z2);

    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
    strTest2.clear();

    //-------------------------------------------

    std::string strTest3; //2.000.000
    size_t strSizeTest3 = 2000000;
    size_t patternSize3 = 200;
    // std::string tmp;
    for (size_t i = 0; i < strSizeTest3; ++i) {
        if (i == patternSize3) {
            tmp = '$';
            strTest3.append(tmp);
            continue;
        }

        if (rand() % 15 == 0) {
            tmp = ' ';
        } else {
            tmp = (rand() % 26) + 'a';
        }

        strTest3.append(tmp);
    }

    std::cout << "TEST 3 - \t SIZE: " << strSizeTest3 << '\n';
    auto start3 = std::chrono::high_resolution_clock::now();

    int Z3[strSizeTest2];
    createZArr(strTest3, Z3);

    auto stop3 = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);

    std::cout << "DONE!\n";
    std::cout << "TEST 1 = " << duration1.count() << '\n';
    std::cout << "TEST 2 = " << duration2.count() << '\n';
    std::cout << "TEST 3 = " << duration3.count() << '\n';

    return 0;
}