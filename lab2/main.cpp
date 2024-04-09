#include "./patricia/Patricia.h"

int main()
{
    TPatricia a;
    a.Insert("abc", 1);
    a.Insert("abd", 2);
    a.Insert("abe", 3);
    a.Insert("abf", 4);

    TNode* find = a.Find("abd");
    if (find) {
        std::cout << "OK: " << find->Value << '\n';
    } else {
        std::cout << "NoSuchWord\n";
    }
    return 0;
}