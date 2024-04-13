#include "./patricia/Patricia.h"

void LowercaseConverter(char* str)
{
    for (size_t i = 0; i < strlen(str); ++i) {
        str[i] = str[i] >= 'A' && str[i] <= 'Z' ? str[i] - 'A' + 'a' : str[i];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::ofstream fout;
    std::ifstream fin;

    const int MAXSIZE = 257; 
    char in[MAXSIZE];
    TValue val;

    TPatricia* trie;
    try {
        trie = new TPatricia();
    } catch (std::bad_alloc & e) {
        std::cout << "ERROR: fail to allocate the requested storage space\n";
        exit(EXIT_SUCCESS);
    }

    TNode* node;

    while (std::cin >> in) {
        if (!std::strcmp(in, "+")) {
            std::cin >> in;
            LowercaseConverter(in);
            std::cin >> val;

            std::cout << (trie->Insert(in, val) ? "OK" : "Exist");
            std::cout << '\n';
        } else if (!std::strcmp(in, "-")) {
            std::cin >> in;
            LowercaseConverter(in);

            std::cout << (trie->Delete(in) ? "OK" : "NoSuchWord");

            std::cout << '\n';
        } else if (!std::strcmp(in, "!")) {
            std::cin >> in;

            if (!std::strcmp(in, "Save")) {
                std::cin >> in;
                fout.open(in, std::ios::out | std::ios::binary | std::ios::trunc);

                trie->Save(fout);
                std::cout << "OK\n";

                fout.close();
            } else if (!std::strcmp(in, "Load")) {
                std::cin >> in;
                fin.open(in, std::ios::in | std::ios::binary);

                delete trie;
                trie = new TPatricia();

                trie->Load(fin);
                std::cout << "OK\n";

                fin.close();
            }
        } else {
            LowercaseConverter(in);
            node = trie->Find(in);

            if (!node) {
                std::cout << "NoSuchWord";
            } else {
                std::cout << "OK: " << node->Value;
            }

            std::cout << '\n';
        }
    }
    
    delete trie;

    return 0;
}