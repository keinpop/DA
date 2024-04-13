#pragma once

#include "Node.h"

class TPatricia
{
public:
    TPatricia();

    TNode* Find(TKey* k);
    TNode* Insert(TKey* k, const TValue & v);
    bool Delete(TKey* k);

    // serialization
    void Save(std::ofstream & file);
    void Load(std::ifstream & file);

    ~TPatricia();

private:
    void recursiveDestructor(TNode* n);

    // This func return 1 or 0 bit 
    // 1 or 0 help to navigate in tree (1 - go right, 0 - go left)
    int getBit(TKey* key, int bit);
    bool keyEqual(TKey* a, TKey* b);
    int firstDiffBit(TKey* a, TKey* b);

    // helpfull for method to serialization
    void enumerateNodesInArray(TNode* root, TNode** arr, int & index) const;

    // this private method help to public method delete with copy DATA in node,
    // when Deleted Node has two sons and they not he
    void keyValueCopy(TNode* src, TNode* dest);

private:
    TNode* Root;
    size_t Size;
};

// IMPLEMENTATION 
TPatricia::TPatricia()
{
    Root = new TNode();
    Size = 0;
}

TNode* TPatricia::Find(TKey *key)
{
    TNode* p = Root;
    TNode* q = Root->Left;

    while (p->Bit < q->Bit) {
        p = q;
        q = (getBit(key, q->Bit) ? q->Right : q->Left);
    }

    if (!keyEqual(key, q->Key)) {
        return 0;
    }

    return q;
}


TNode* TPatricia::Insert(TKey *key,const TValue & value)
{
    TNode* parent = Root; // Help to navigate
    TNode* child = Root->Left; // Where insert
    while (parent->Bit < child->Bit) {
        parent = child;
        child = (getBit(key, child->Bit) ? child->Right : child->Left);
    }

    // If the key already exists
    if (keyEqual(key, child->Key)) {
        return 0;
    }

    int lBitPos = firstDiffBit(key, child->Key);

    parent = Root;
    TNode* tmp = Root->Left; // start to left son ROOT

    while (parent->Bit < tmp->Bit && tmp->Bit < lBitPos) {
        parent = tmp;
        tmp = (getBit(key, tmp->Bit) ? tmp->Right : tmp->Left);
    }

    try {
        child = new TNode();
    } catch (const std::bad_alloc &e) {
        std::cout << "ERROR: fail to allocate the requested storage space\n";
        return 0;
    }

    // if bit key has 1, then left node was tmp (right)
    child->Init(lBitPos, key, value,
                    (getBit(key, lBitPos) ? tmp : child),
                    (getBit(key, lBitPos) ? child : tmp));

    if (getBit(key, parent->Bit)) {
        parent->Right = child;
    } else {
        parent->Left = child;
    }

    Size++;
    return child;
}


bool TPatricia::Delete(TKey* k) 
{
    // gp - parent element for the node to be deleted, p - parent,
    // t - to be deleted node
    TNode* pp, *p, *t = 0;

    p = Root;
    t = (p->Left);

    // find gp, p, t
    while (p->Bit < t->Bit) {
        pp = p;
        p = t;
        t = (getBit(k, t->Bit) ? t->Right : t->Left);
    }

    // if key not found
    if (!keyEqual(k, t->Key)) {
        return false;
    }

    TNode* x, *r;
    char* key;
    // если p == t, то есть есть ссылка на самого себя,
    // значит мы можем просто перевесить указатель к gp наш
    // указатель t, который ссылается на себя
    if (p != t) {
        keyValueCopy(p, t);

        key = p->Key;
        r = p;
        x = (getBit(key, p->Bit) ? p->Right : p->Left);

        // ищем тот узел, который ссылается на p обратным указателем
        // то есть в r будет лежать этот элемент,
        // а в x будет лежать p

        while (r->Bit < x->Bit) {
            r = x;
            x = (getBit(key, x->Bit) ? x->Right : x->Left);
        }

        // теперь перевесим указатель с p на t
        if (getBit(key, r->Bit)) {
            r->Right = t;
        } else {
            r->Left = t;
        }
    }
    
    TNode* ch = (getBit(k, p->Bit) ? p->Left : p->Right);
    if (getBit(k, pp->Bit)) {
        pp->Right = ch;
    } else {
        pp->Left = ch;
    }

    delete p;
    --Size;

    return true;
}

void TPatricia::Save(std::ofstream &file)
{
    // Step 1 - write sizeof our trie
    file.write((const char* )&(Size), sizeof(int));

    // Step 2 - enumerate all nodes in trie, init array of pointers
    int index = 0;
    TNode **nodes;
    try {
        nodes = new TNode *[Size + 1];
    } catch (const std::bad_alloc &e) {
        std::cout << "ERROR: fail to allocate the requested storage space\n";
        return;
    }
    enumerateNodesInArray(Root, nodes, index);

    // At now sequenitally write all info of node
    TNode *node;
    for (int i = 0; i < (Size + 1); ++i) {
        node = nodes[i];
        file.write((const char* )&(node->Value), sizeof(TValue));
        file.write((const char* )&(node->Bit), sizeof(int));
        int len = node->Key ? strlen(node->Key) : 0;
        file.write((const char* )&(len), sizeof(int));
        file.write(node->Key, sizeof(char) * len);
        file.write((const char* )&(node->Left->Id), sizeof(int));
        file.write((const char* )&(node->Right->Id), sizeof(int));
    }

    delete[] nodes;
}


void TPatricia::Load(std::ifstream &file)
{
    // reading size of trie
    int n;
    file.read((char* )&n, sizeof(int));
    Size = n;

    if (!Size) {
        return;
    }

    TNode **nodes = new TNode *[Size + 1];
    // because the root is already created in the constructor
    nodes[0] = Root;
    for (int i = 1; i < (Size + 1); ++i) {
        nodes[i] = new TNode();
    }

    // variables of to need read
    int bit;
    int len;
    TKey* key = 0;
    TValue value;
    int idL, idR;

    for (int i = 0; i < (Size + 1); ++i) {
        file.read((char* )&(value), sizeof(TValue));
        file.read((char* )&(bit), sizeof(int));
        file.read((char* )&(len), sizeof(int));
        if (len) {
            key = new char[len + 1];
            key[len] = 0;
        }
        
        file.read(key, len);
        file.read((char* )&(idL), sizeof(int));
        file.read((char* )&(idR), sizeof(int));
        nodes[i]->Init(bit, key, value, nodes[idL], nodes[idR]);
        delete[] key;
    }

    delete[] nodes;

    return;
}


TPatricia::~TPatricia()
{
    recursiveDestructor(Root);
}

void TPatricia::recursiveDestructor(TNode* n)
{
    if (n->Left->Bit > n->Bit) {
        recursiveDestructor(n->Left);
    } 

    if (n->Right->Bit > n->Bit) {
        recursiveDestructor(n->Right);
    }

    delete n;
}

void TPatricia::enumerateNodesInArray(TNode* r, TNode** arr, int & idx) const
{
    // id of Nodes not repeat, but send to reference
    r->Id = idx; 
    arr[idx] = r;
    ++idx;

    if (r->Left->Bit > r->Bit) {
        enumerateNodesInArray(r->Left, arr, idx);
    } 
    
    if (r->Right->Bit > r->Bit) {
        enumerateNodesInArray(r->Right, arr, idx);
    }
}

int TPatricia::getBit(TKey* key, int bit) 
{
    if (bit < 0) {
        bit = 0;
    }

    const int SENIOR_RANK = 7;
    const int COUNT_OF_BIT = 8;
    // We take bit in string key and make bit shift, then to compute conjunction with 1
    return (key[bit / COUNT_OF_BIT] >> (SENIOR_RANK - (bit % COUNT_OF_BIT))) & 1;
}

bool TPatricia::keyEqual(TKey* a, TKey* b)
{
    if (a == 0 || b == 0) {
        return false;
    }

    return (strcmp(a, b) == 0);
}

int TPatricia::firstDiffBit(TKey* a, TKey* b)
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
    while (getBit(a, pos) == getBit(b, pos)) {
        pos++;
    }

    return pos;
}

void TPatricia::keyValueCopy(TNode* src, TNode* dest)
{
    if (strlen(dest->Key) < strlen(src->Key)) {
        delete[] dest->Key;
        dest->Key = new TKey[strlen(src->Key) + 1];
    }

    strcpy(dest->Key, src->Key);
    dest->Value = src->Value;
}