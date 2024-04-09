#include "Node.h"

class TPatricia
{
public:
    TPatricia()
    {
        Root = new TNode();
        Size = 0;
    }

    TNode* Find(TKey* k)
    {
        TNode* parent = Root;
        TNode* child = Root->Left;

        while (parent->Bit < child->Bit) {
            parent = child;
            child = (GetBit(k, child->Bit) ? child->Right : child->Left);
        }

        if (!KeyEqual(k, child->Key)) {
            return 0;
        }

        return child;
    }

    TNode* Insert(TKey* k, const TValue & v)
    {
        TNode* parent = Root; // Help to navigate
        TNode* child = Root->Left; // Where insert

        while (parent->Bit < child->Bit) {
            parent = child;
            child = (GetBit(k, child->Bit) ? child->Right : child->Left);
        }

        // If the key already exists
        if (KeyEqual(k, child->Key)) {
            return 0; 
        }

        int lBitPos = FirstDiffBit(k, child->Key);

        parent = Root;
        TNode* tmp = Root->Left; // start to left son ROOT

        while (parent->Bit < tmp->Bit && tmp->Bit < lBitPos) {
            parent = tmp;
            tmp = (GetBit(k, tmp->Bit) ? tmp->Right : tmp->Left);
        }

        try {
            child = new TNode();
        } catch (const std::bad_alloc & e) {
            std::cout << "ERROR: fail to allocate the requested storage space\n";
            return 0;
        }

        child->Init(
            lBitPos,
            k,
            v,
            (GetBit(k, lBitPos) ? tmp : child), // if bit key has 1, then left node was tmp (right)
            (GetBit(k, lBitPos) ? child : tmp)
        );

        if (GetBit(k, parent->Bit)) {
            parent->Right = child;
        } else {
            parent->Left = child;
        }

        ++Size;
        
        return child;
    }

    ~TPatricia()
    {
        RecursiveDestructor(Root);
    }

private:
    void RecursiveDestructor(TNode* n)
    {
        if (n->Left->Bit > n->Bit) {
            RecursiveDestructor(n->Left);
        } 

        if (n->Right->Bit > n->Bit) {
            RecursiveDestructor(n->Right);
        }

        delete n;
    }
    // This func return 1 or 0 bit 
    // 1 or 0 help to navigate in tree (1 - go right, 0 - go left)
    static inline int GetBit(TKey* key, int bit) 
    {
        if (bit < 0) {
            bit = 0;
        }

        const int SENIOR_RANK = 7;
        const int COUNT_OF_BIT = 8;
        // We take bit in string key and make bit shift, then to compute conjunction with 1
        return (key[bit / COUNT_OF_BIT] >> (SENIOR_RANK - (bit % COUNT_OF_BIT))) & 1;
    }

    static inline bool KeyEqual(TKey* a, TKey* b)
    {
        if (a == 0 || b == 0) {
            return false;
        }

        return (strcmp(a, b) == 0);
    }

    static inline int FirstDiffBit(TKey* a, TKey* b)
    {
        if (a == 0 || b == 0) {
            return 0;
        }

        int pos = 0;

        //step to byte in keys
        while (a[pos] == b[pos]) {
            pos++;
        }

        // convert byte to bit
        pos *= 8;

        // step to bit in keys
        while (GetBit(a, pos) == GetBit(b, pos)) {
            pos++;
        }

        return pos;
    }

    // this private method help to public method delete with swap DATA in node,
    // when Deleted Node has two sons and they not he
    void KeyValueCopy(TNode* src, TNode* dest)
    {
        
    }

private:
    TNode* Root;
    size_t Size;
};