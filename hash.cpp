#include <iostream>
#include "hash.h"
#include <vector>
#include <string>
#include <list>
#include "limits.h"
//global
const int primelist[26] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 
24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 
12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
//func_def



hashTable::hashTable(int size){
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}


int hashTable::insert(const std::string &key, void *pv){
    if(contains(key)) return 1;
    int index = hash(key);
    int inc =  hash2(key);
    index %= capacity;
    int counter = 0;
    while (data[index].isOccupied && !data[index].isDeleted) {
        index += inc;
        index %= capacity;
        if ((++counter) > capacity)
        throw std::runtime_error("NOOOOOOO SPAAAACE");
    }
    filled++;
    if(filled > capacity>>1) if(!rehash()) return 2;
    data[index].isOccupied=true;
    data[index].isDeleted=false;
    data[index].key=key;
    data[index].pv = pv;
    return 0;
}

bool hashTable::contains(const std::string &key){
    return (findPos(key)+1);
}

void * hashTable::getPointer(const std::string &key, bool *b ){
    int pos = findPos(key);
    *b = false;
    if (pos == -1)  return nullptr;
    *b = true;
    return data[pos].pv;
}

int hashTable::setPointer(const std::string &key, void *pv){
    int pos = findPos(key);
    if (pos == -1)  return 1;
    data[pos].pv = pv;
    return 0;
}

bool hashTable::remove(const std::string &key){
    int pos = findPos(key);
    if(pos == -1)   return false;
    data[pos].isDeleted = true;
    filled --;
    return true;
}

int hashTable::hash(const std::string &key){
    int len = key.length();
    unsigned long hash = 5381;
    for(int i = 0; i < len; i++){
        hash = (hash << 5 + hash);
        hash += key[i];
        hash %= INT_MAX;
    }
    return hash;
}
int hashTable::hash2(const std::string &key){
    int len = key.length();
    unsigned long hash = 0;
    for(int i = 0; i < len; i++){
        hash = key[i] + (hash << 6) + (hash << 16) - hash;
        hash %= INT_MAX;
    }
    hash %= 6151;
    hash += 7;
    return hash;
}
int hashTable::findPos(const std::string &key){
    int index = hash(key);
    int inc =  hash2(key);
    index %= capacity;
    while(data[index].isOccupied)
    {
        if(data[index].key == key){
            if(data[index].isDeleted)   return -1;
            return index;
        }
        index += inc;
        index %= capacity;
    }
    return -1;
}
bool hashTable::rehash(){
    int cap =  capacity;
    capacity = getPrime(capacity);
    if(cap == capacity) return false;
    std::vector<hashItem> old_data = data;
    data.clear();
    data.resize(capacity);
    filled = 0;
    for(int i = 0; i < cap; i++)
    {
        if(old_data[i].isOccupied && !old_data[i].isDeleted)    insert(old_data[i].key, old_data[i].pv);
    }
    old_data.clear();
    return true;
}
unsigned int hashTable::getPrime(int size){
    size <<= 1;
    for (int i = 0; i < 26; i++)
    {
        if(primelist[i]>size) return primelist[i];
    }
    throw std::runtime_error ("size invalid");
    return primelist[25];
}