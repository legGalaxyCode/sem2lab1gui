#ifndef MODEL_H
#define MODEL_H
//model is a data (graph) storage
//only this file need to change
//just add ur graph presentation
//and algorithms realisation

#include<iostream>
#include<vector>
#include<utility>

//using namespace std;

//singleton model
class Model //may not be inherite of QWidget
{
private:
    Model();
    std::vector<std::vector<std::pair<int, int>>> graph; // my graph for example
    static Model* model;
public:
    Model(Model& other) = delete;
    void operator=(const Model&) = delete;
    static Model* getInstance(); //pass args in constructor if needed
    ~Model(){};
    void readGraphFromBinFile();
    void readGraphFromTxtFile();
    void generateGraph(); //pass N, M, graph
    void Dijkstra(); //pass graph
    void BellmanFord(); //pass graph
    void FloydUorshell(); //pass graph
};

#endif // MODEL_H
