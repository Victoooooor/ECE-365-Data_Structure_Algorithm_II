#include <iostream>
#include <string>
#include <vector>
#include "dxta.h"
#include <fstream>
#include <ctime>

using namespace std;

int main(){
    ifstream input;
    string buffer;
    do{
        cout << "Enter name of graph file: ";
        cin >> buffer;
        input.open(buffer);
    }while(!input);
    vector<string> load;
    while(input){
        getline(input, buffer);
        load.push_back(buffer);
    }
    graph mapp(load);
    load.clear();
    clock_t t1;
    clock_t t2;
    int ret;
TAG:
        cout << "Enter a valid vertex id for the staring vertex: ";
        cin >> buffer;
        t1 = clock();
        ret = mapp.Dijkstra(buffer);
        t2 = clock();
    if(ret)   goto TAG;
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
    ofstream output;
    do{
        cout << "Enter name of output file: ";
        cin >> buffer;
        output.open(buffer);
    }while(!output.is_open());
    mapp.printdx(&output);
    return 0;
}