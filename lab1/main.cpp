#include "./Vector.h"

int main()
{
    char c;
    
    TVector<char> str;
    TVector<TSortType> vec;

    uint64_t val;

    while (scanf("%c", &c) == 1) {
        if (c == '\n') {
            continue;
        }

        if (c == ' ' || c == '\t') {
            TSortType tmp;
            tmp.Key.Data = str;
            scanf("%llu", &val);
            tmp.Value = val;
            vec.PushBack(tmp);
            str.Clear();
            continue;
        }
        str.PushBack(c);
    }

    for (int i = 0; i < vec.GetSize(); ++i) {
        int countPow = 1;
        int tmpDigit = 0;
        bool d = false, m = false, y = true;

        uint64_t calculateAllDays = 0;
        for (int j = vec[i].Key.Data.GetSize() - 1; j >= 0; --j) {
            if (vec[i].Key.Data[j] == '.') {
                if (y) {
                    calculateAllDays += tmpDigit * 365;
                    tmpDigit = 0;
                    countPow = 1;
                    y = false;
                    m = true;
                    continue;
                }

                if (m) {
                    calculateAllDays += tmpDigit * 30;
                    tmpDigit = 0;
                    countPow = 1;
                    m = false;
                    d = true;
                    continue;
                }

                continue;
            }

            int dig = vec[i].Key.Data[j] - '0';
            
            tmpDigit += dig * countPow;
            countPow *= 10;

            if (j == 0 && d) {
                
                calculateAllDays += tmpDigit;
                tmpDigit = 0;
                countPow = 1;
                d = false;
                y = true;
            } 
        }
        
        vec[i].Key.Days = calculateAllDays;
        
    }

    for (int i = 0; i < vec.GetSize(); ++i) {
        std::cout << vec[i].Key.Days << std::endl;
    }


    return 0;
}