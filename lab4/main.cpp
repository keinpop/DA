#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>

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
    std::ifstream fIn("input.txt");

    // Счетчик слов в каждой строке, то есть размер
    // этого вектора равен количеству строк
    std::vector<size_t> countOfWordsInStr;

    std::string pattern;
    // Считываем паттерн и приводим к удобному для 
    // нас формату (нижний регистр, лишние пробелы)
    std::getline(fIn, pattern);
    removeExtraSpace(pattern);

    // Подсчитываем количество слов в паттерне
    size_t coutOfWordsInPattern = 0;

    for (auto & c : pattern) {
        if (c == ' ') {
            ++coutOfWordsInPattern;
        }
    }
    // Так как после последнего слова нет пробела
    // добавим еще одно слово
    ++coutOfWordsInPattern;

    std::string buff;

    // Заведем нашу исходную БОЛЬШУЮ строку
    // для работы с z-алгоритмом
    std::string resString;

    resString.append(pattern);
    resString.append("$"); // синтенел

    while (std::getline(fIn, buff)) {
        std::replace(buff.begin(), buff.end(), '\n', ' ');
        removeExtraSpace(buff);

        size_t wordCounter = 0;

        if (!buff.empty()) {
            for (auto & c : buff) {
                if (c == ' ') {
                    ++wordCounter;
                }
            }

            ++wordCounter;

            resString.append(buff + ' ');
        }

        countOfWordsInStr.push_back(wordCounter);
    }

    // Удалим последний пробел в строке
    resString.pop_back();

    // Посчитаем префикс сумму для того, чтобы
    // когда мы искали подстроку, понимали, что 
    // паттерн может начаться на одной строке,
    // а закончится на другой
    for (size_t i = 1; i < countOfWordsInStr.size(); ++i) {
        countOfWordsInStr[i] = countOfWordsInStr[i] + countOfWordsInStr[i - 1];
    }

    // Создание Z-массива
    int zArr[resString.size()];
    createZArr(resString, zArr);

    size_t wordsCounterInResStr = 1;

    // Зададим индексы начала строки и конца
    size_t firstPos = pattern.size() + 1; // + 1, т.к. есть синтенел
    size_t nextPos = resString.find(' ', firstPos);
    
    for (size_t i = 1; i < coutOfWordsInPattern; ++i) {
        nextPos = resString.find(' ', nextPos + 1); // 
    }

    if (nextPos == std::string::npos) {
        nextPos = resString.size();
    }
    
    for (size_t i = pattern.size() + 1; i < resString.size(); ++i) {
        if (resString[i] == ' ') {
            ++wordsCounterInResStr;
            firstPos = i + 1;
            nextPos = resString.find(' ', nextPos + 1);
            if (nextPos == std::string::npos) {
                nextPos = resString.size();
            }
        }


        if (zArr[i] == pattern.size() && (nextPos - firstPos) == pattern.size()) {
            int j = 0;
            for ( ; j < countOfWordsInStr.size(); ++j) {
                if (wordsCounterInResStr <= countOfWordsInStr[j]) {
                    break;
                }
            }

            int word;

            if (j == 0) {
                word = wordsCounterInResStr;
            } else {
                word = wordsCounterInResStr - countOfWordsInStr[j - 1];
            }

            std::cout << j + 1 << ", " << word << '\n';
        }
    }

    return 0;
}