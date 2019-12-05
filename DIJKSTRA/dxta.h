#ifndef _DXTA_H
#define _DXTA_H

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "hash.h"
#include "heap.h"
#include "limits.h"

class graph{
public:
    graph(vector<string> gen);
    int Dijkstra(std::string source);
    void printdx(ofstream* output);
private:
    class vertex;
    struct destin{
        vertex* id; //postion in data
        int dist;
    };
    class vertex{
    public:
        std::string id;
        vertex* prev = nullptr;
        std::list<destin> edge;
        int keyd = INT_MAX;
    };
    std::list<vertex> data; //loaded data with order in vector
    hashTable vcheck; //check if in data
    heap distance; //use deleteMin for distance
    int insert(std::string sv, std::string dv, int dis);
};

#endif