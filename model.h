#ifndef MODEL_H
#define MODEL_H
//model is a data (graph) storage
//only this file needs to change
//just add ur graph presentation
//and algorithms realisation

//& delete all boost references

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <random>
#include <ctime>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>

//using namespace std;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::property<boost::edge_weight_t, int>> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<Graph>::edge_descriptor edge_descriptor;
typedef std::pair<int, int> Edge; //first is start, second is end

//singleton model
class Model //may not be inherite of QWidget
{
private:
    Model();
    const int M = rand() % 20 + 5;
    const int K = rand() % 10 + 5;
    const unsigned V = 10000 / M; //vertices
    const unsigned long E = V * (K*4); //edges
    const unsigned max_weight = 50;
    std::vector<std::vector<Edge>> graph{V}; // my graph for example, first = vertex, second = weight
    Graph boost_graph; //graph for boost
    std::vector<Edge> edge;
    std::map<Edge, int> weight_map;
    std::vector<int> weight_v;
    std::vector<vertex_descriptor> parent;
    std::vector<int> distance;
    vertex_descriptor start_vertex;
    boost::property_map<Graph, boost::edge_weight_t>::type b_w_map;
    static Model* model;
public:
    Model(Model& other) = delete;
    void operator=(const Model&) = delete;
    static Model* getInstance(); //pass args in constructor if needed
    ~Model(){};
    std::vector<std::vector<Edge>> getGraph();
    Graph get_boost_graph();
    std::pair<Graph, std::vector<int>> get_weight_graph();
    void set_weight_graph(std::pair<Graph, std::vector<int>>);
    std::pair<std::vector<vertex_descriptor>, std::vector<int>> get_graph_opt();
    std::pair<unsigned, unsigned long> sizeGraph();
    void generateGraph(); //pass N, M, graph, ur algo
    void generateBoostGraph();
    void Dijkstra(); //pass graph, ur algo
    void boostDijkstra();
    void BellmanFord(); //pass graph, ur algo
    void boostBellman();
    void FloydUorshell(); //pass graph, ur algo
    void boostFloyd();
};

#endif // MODEL_H
