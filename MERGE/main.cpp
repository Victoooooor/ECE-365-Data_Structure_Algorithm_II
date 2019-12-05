#include <iostream>
#include <fstream>
#include <string>

//global data
std::string A(1001, ' ');
std::string B(1001, ' ');
std::string C(2002, ' ');
bool path[1002][1002] = {false};

//function declare
namespace merge{
    bool read(std::ifstream* INPUT);
    void init();
    bool pathfind();
    void write(bool state, std::ofstream* OUTPUT);
}

//Assemblly!!
int main(){
    //input output conf
    std::ifstream input;
    std::ofstream output;
    std::string buffer;
    do{
        std::cout << "Enter Input File Name: ";
        std::cin >> buffer;
        input.open(buffer);
    }while(!input);
    do{
        std::cout << "Enter Output File Name: ";
        std::cin >> buffer;
        output.open(buffer);
    }while(!output.is_open());
    //process
    while(merge::read(&input)){
        merge::init();
        merge::write(merge::pathfind(), &output);
    }
    return 0;
}

bool merge::read(std::ifstream* INPUT){
    if(!std::getline(*INPUT, A))    return false;
    if(!std::getline(*INPUT, B))    return false;
    if(!std::getline(*INPUT, C))    return false;
    A += '\n';
    B += '\n';
    C += "\n\n";
    return true;
}

void merge::init(){
    for(int i = 0; i <= A.length(); i++){
        for(int j = 0; j <= B.length(); j++)    path[i][j] = false;
    }
    path[0][0] = true;
}

bool merge::pathfind(){
    if(A.length()+B.length() != C.length()) return false;
    for(int i = 0; i < A.length(); i++){
        for(int j = 0; j < B.length(); j++){
            if(!path[i][j]) continue;
            if(C[i+j] == B[j])  path[i][j+1] = true;
            if(C[i+j] == A[i])  path[i+1][j] = true;
        }
    }
    return path[A.length()-1][B.length()-1];
}

void merge::write(bool state, std::ofstream* OUTPUT){
    if(!state)  {
        *OUTPUT<<"*** NOT A MERGE ***\n";
        return;
    }
    int ai = A.length()-1;
    int bi = B.length()-1;
    while(ai&&bi){
        if(path[ai][bi-1])  bi--; 
        else if(path[ai-1][bi]){
            ai--;
            C[ai+bi] = std::toupper(C[ai+bi]);
        }
    }
    if(!bi){
        for(int i = 0; i < ai; i++){
            C[i] = std::toupper(C[i]);
        }
    }
    C.pop_back();
    *OUTPUT<<C;
}