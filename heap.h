#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include "hash.h"

using namespace std;

class heap{
public:
    heap(int capacity);
    int insert(const std::string &id, int key, void *pv = nullptr); //check
    int setKey(const std::string &id, int key); //check
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);
    void heapprint(); //
private:
    class node{
        public:
        string id;
        int key;
        void *pData;
    };
    int currentsize;
    int lim;
    vector<node> data;
    hashTable mapping;
    void percolateUp(int posCur); //check
    void percolateDown(int posCur); //check
    int getPos(node *pn); //check
};

#endif