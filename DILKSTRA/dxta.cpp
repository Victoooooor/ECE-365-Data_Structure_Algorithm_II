#include <iostream>
#include <list>
#include <string>
#include "dxta.h"
#include <sstream>
#include "limits.h"

using namespace std;

graph::graph(vector<string> gen):distance(gen.size()*2), vcheck(gen.size()*2){
    string sv;
    string dv;
    int dis;
    for(int i =0; i < gen.size(); i++){
        stringstream ss(gen[i]);
        ss >> sv >> dv >> dis;
        insert(sv, dv, dis);
    }
}

int graph::insert(std::string sv, std::string dv, int dis){
    bool exist, exist2;
    vertex temp;
    vertex* vptr = static_cast<vertex *> (vcheck.getPointer(sv, &exist));
    vertex* vptr2 = static_cast<vertex *> (vcheck.getPointer(dv, &exist2));
    if(!exist){
        temp.id = sv; temp.keyd = INT_MAX;
        data.push_back(temp);
        vcheck.insert(sv, &data.back());
        vptr = &data.back();
    }
    if(!exist2){
        temp.id = dv; temp.keyd = INT_MAX;
        data.push_back(temp);
        vcheck.insert(dv, &data.back());
        vptr2 = &data.back();
    }
    destin adds;
    adds.dist = dis;
    adds.id = vptr2;
    vptr->edge.push_back(adds);
    return 0;
}

int graph::Dijkstra(string source){
    bool exist;
    vertex* vptr = static_cast<vertex *> (vcheck.getPointer(source, &exist));
    if(!exist) return 1;
    vptr->keyd = 0;
    distance.insert(vptr->id, 0, vptr);
    int pre;
    void* pptr;
    while(!distance.deleteMin(nullptr, &pre, &pptr)){
        vptr = static_cast<vertex *> (pptr);
        for(auto i : vptr->edge){
            if(i.dist+pre >= i.id->keyd) continue;
            int nd = pre+i.dist;
            if(distance.setKey(i.id->id, nd))   distance.insert(i.id->id, nd, i.id);
            i.id->keyd = nd;
            i.id->prev = vptr;
        }
    }
    return 0;
}

void graph::printdx(ofstream* output){
    string buffer;
    for(auto i : data){
        if(i.keyd == INT_MAX){
            *output << i.id << ": NO PATH\n";
            continue;
        }
        *output << i.id << ": " << i.keyd << " " << "[";
        vertex* j = &i;
        buffer.clear();
        buffer += j->id;
        while(j->prev != nullptr){
            j = j->prev;
            buffer =  j->id+", "+buffer;
            
        }
        *output << buffer;
        *output << "]\n";
    }
}