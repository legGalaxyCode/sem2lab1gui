#ifndef MODEL_H
#define MODEL_H
//model is a data (graph) storage
//only this file need to change
//just add ur graph presentation
//and algorithms realisation

#include<iostream>
#include<vector>
#include<utility>
#include<random>
#include<ctime>

//using namespace std;

//singleton model
class Model //may not be inherite of QWidget
{
private:
    Model();
    const int M = rand() % 20 + 5;
    const int K = rand() % 10 + 5;
    const unsigned V = 1000000/M;
    const unsigned long E = V * (K*K);
    std::vector<std::vector<std::pair<int, int>>> graph{V}; // my graph for example, first = vertex, second = weight
    static Model* model;
public:
    Model(Model& other) = delete;
    void operator=(const Model&) = delete;
    static Model* getInstance(); //pass args in constructor if needed
    ~Model(){};
    std::vector<std::vector<std::pair<int, int>>> getGraph();
    std::pair<unsigned, unsigned long> sizeGraph();
    void readGraphFromBinFile();
    void readGraphFromTxtFile();
    void generateGraph(); //pass N, M, graph
    void Dijkstra(); //pass graph
    void BellmanFord(); //pass graph
    void FloydUorshell(); //pass graph
};

#endif // MODEL_H
