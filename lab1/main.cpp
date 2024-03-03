#include "./Sort.h"

int main()
{
    char c;
    
    TVector<char> str;
    TVector<TSortType*> vec;

    unsigned long long val;
    while (c = getchar_unlocked()) {
        if (c == EOF) {
            break;
        }
        
        if (c == '\n') {
            continue;
        }

        if (c == ' ' || c == '\t') {
            TSortType* tmp = new TSortType;
            tmp->Key.Data = str;
            scanf("%llu", &val);
            tmp->Value = val;
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

        unsigned long long calculateAllDays = 0;

        for (int j = vec[i]->Key.Data.GetSize() - 1; j >= 0; --j) {
            if (vec[i]->Key.Data[j] == '.') {
                if (y) {
                    const int COUNT_OF_DAYS_IN_YEAR = 365;
                    calculateAllDays += tmpDigit * COUNT_OF_DAYS_IN_YEAR;
                    tmpDigit = 0;
                    countPow = 1;
                    y = false;
                    m = true;
                    continue;
                }

                if (m) {
                    const int COUNT_OF_DAYS_IN_MONTH = 30;
                    calculateAllDays += tmpDigit * COUNT_OF_DAYS_IN_MONTH;
                    tmpDigit = 0;
                    countPow = 1;
                    m = false;
                    d = true;
                    continue;
                }

                continue;
            }

            int dig = vec[i]->Key.Data[j] - '0';
            
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
        vec[i]->Key.Days = calculateAllDays;
    }

    RadixSort(vec);

    PrintArrayTSortType(vec);

    for (int i = 0; i < vec.GetSize(); ++i) {
        delete vec[i];
    }

    return 0;
}