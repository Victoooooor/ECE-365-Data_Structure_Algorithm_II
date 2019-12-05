#include <iostream>
#include <string>
#include <vector>
#include "heap.h"

heap::heap(int capacity):mapping(capacity){
    data.resize(capacity+1);
    lim = capacity;
    currentsize = 0;
}

int heap::insert(const std::string &id, int key, void *pv){
    if(currentsize == lim)  return 1;
    if(mapping.contains(id))    return 2;
    currentsize++;
    data[currentsize].id = id;
    data[currentsize].key = key;
    data[currentsize].pData = pv;
    mapping.insert(id, &data[currentsize]);
    percolateUp(currentsize);
    return 0;
}

int heap::setKey(const std::string &id, int key){
    bool exist;
    node* nptr = static_cast<node *> (mapping.getPointer(id, &exist));
    if(!exist)  return 1;
    int origin = nptr->key;
    nptr->key = key;
    if(origin > key)  percolateUp(getPos(nptr));
    if(origin < key)  percolateDown(getPos(nptr));
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (!currentsize) return 1;
    mapping.remove(data[1].id);
    data[0] = data[currentsize];
    data[currentsize] = data[1];
    data[1] = data[0];
    if (pId   != nullptr) *pId  = data[currentsize].id;
	if (pKey  != nullptr) *pKey = data[currentsize].key;
	if (ppData!= nullptr) *(static_cast<void **> (ppData)) = data[currentsize].pData;
    currentsize--;
    mapping.setPointer(data[1].id, &data[1]);
    percolateDown(1);
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
    bool exist;
    node* nptr = static_cast<node *> (mapping.getPointer(id, &exist));
    if (!exist) return 1;
    int pos = getPos(nptr);
    mapping.remove(nptr->id);
    data[0] = data[currentsize];
    data[currentsize] = data[pos];
    data[pos] = data[0];
    mapping.setPointer(data[pos].id, &data[pos]);
	if (pKey  != nullptr) *pKey = data[currentsize].key;
	if (ppData!= nullptr) *(static_cast<void **> (ppData)) = data[currentsize].pData;
    currentsize--;
    if (data[pos].key > data[currentsize+1].key)    percolateDown(pos);
    if (data[pos].key < data[currentsize+1].key)    percolateUp(pos);
    return 0;
}

void heap::percolateUp(int posCur){
    data[0] = data[posCur];
    for(; posCur > 1; posCur /= 2){
        if(data[posCur/2].key > data[0].key)   data[posCur] = data[posCur/2];
        else    break;
        mapping.setPointer(data[posCur].id, &data[posCur]);
    }
    data[posCur] = data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolateDown(int posCur){
    data[0] = data[posCur];
    int temp;
    while((posCur*2) <= currentsize){
        temp = posCur*2;
        if ((posCur*2+1) <= currentsize)    if(data[posCur*2+1].key < data[posCur*2].key)   temp = (posCur*2+1);
        if (data[temp].key > data[0].key)   break;
        data[posCur] = data[temp];
        mapping.setPointer(data[posCur].id, &data[posCur]);
        posCur = temp;
    }
    data[posCur] = data[0];
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(heap::node *pn){return  (pn - &data[0]);}

void heap::heapprint(){
    int counter = 0;
    int counting = 0;
    int limit = 1;
    cout<<endl<<endl<<endl<<"start:"<<endl;
    for(auto i :data)
    {
        if(counter>currentsize)
        break;
        
        if (counter)
        {
            //cout<< "Index:"<<counter;
            cout<< "\tid:"<<i.id;
            cout<< "\tkey:"<<i.key<<"\t";
            counting++;
            if(counting == limit)
            {
                cout<<endl;
                counting = 0;
                limit *= 2;
            }
        }
        counter++;
    }
}