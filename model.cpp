//delete my realisation and write ur own
//in not *boost slots

#include<model.h>

Model* Model::model = nullptr;

Model* Model::getInstance() {
    if (model == nullptr) {
        model = new Model; //pass args if needed
    }
    return model;
}

Model::Model(){};

std::vector<std::vector<std::pair<int, int>>> Model::getGraph() {
    return graph;
}

Graph Model::get_boost_graph() {
    return boost_graph;
}

std::pair<Graph, std::vector<int>> Model::get_weight_graph() {
    return std::make_pair(boost_graph, weight_v);
}

std::pair<std::vector<vertex_descriptor>, std::vector<int>> Model::get_graph_opt() {
    return std::make_pair(parent, distance);
};

std::pair<unsigned, unsigned long> Model::sizeGraph() {
    return std::make_pair(V, E);
}

void Model::set_weight_graph(std::pair<Graph, std::vector<int>> g) {
    boost_graph = g.first;
    weight_v = g.second;
}

void Model::generateGraph() { //generate NOT boost graph all verteces over 0
    srand(time(NULL));

    auto tmp = 0;
    for (auto it = 1; it < V; ++it) {
        graph.at(0).push_back(Edge{it, (rand() % max_weight + 1)});
        graph.at(it).push_back(Edge{0, (rand() % max_weight + 1)});
        ++tmp;
    }

    while (tmp != E) {
        auto u = rand() % (V - 1) + 1;
        auto v = rand() % (V - 1) + 1;
        if (u == v)
            while ( u != v)
                u = rand() % (V - 1) + 1;
        graph.at(u).push_back(Edge{v, (rand() % max_weight + 1)});
        graph.at(v).push_back(Edge{u, (rand() % max_weight + 1)});
        tmp++;
    }
}

void Model::generateBoostGraph() { //generate BOOST graph
    //generate boost graph
    //need to implement like a variant mode
    srand((unsigned) time(NULL));
    edge.reserve(V);
    weight_v.reserve(V);

    for (int it = 0; it < E; ++it) {
        auto W = rand() % max_weight + 1;
        auto start_v = rand() % V;
        auto end_v = rand() % V;
        //if start == end again
        //without loops
        while (start_v == end_v) {
            start_v = rand() % V;
            end_v = rand() % V;
        }
        auto start_opt = std::find(edge.begin(), edge.end(), Edge{start_v, end_v}); //if edge already contains {start_v, end_v}
        auto end_opt = std::find(edge.begin(), edge.end(), Edge{end_v, start_v}); //if edge already contains {end_v, start_v}
        if (start_opt != edge.end() || end_opt != edge.end()) {
            --it; // so real num of edges will equal max_edge num
        } else {
            edge.push_back(std::make_pair(start_v, end_v));
            weight_map.emplace(std::make_pair(start_v, end_v), W);
            weight_v.push_back(W); //in order of edges
        }
    }

    boost_graph = Graph(edge.begin(), edge.end(), weight_v.begin(), V);

    //containers of next algorithms
    parent = std::vector<vertex_descriptor>(boost::num_vertices(boost_graph));
    distance = std::vector<int>(boost::num_vertices(boost_graph));
    start_vertex = boost::vertex(0, boost_graph);
    b_w_map = boost::get(boost::edge_weight, boost_graph);
}

void Model::Dijkstra() { //write UR realisation here
    const unsigned CH = 1000000;
    int startV = 0;
    std::vector<int> dijkstra(V, CH), parents(V);
    dijkstra[startV] = 0;
    std::vector<char> marks(V);

    for (auto i = 0; i < V; ++i) {
        auto burn = -1;
        for (auto j = 0; j < V; ++j)
            if (!marks[j] && (burn == -1 ||
                              dijkstra[j] < dijkstra[burn]))
                burn = j;
        if (dijkstra[burn] == CH)
            break;
        marks[burn] = true;

        for (auto j = 0; j < graph[burn].size(); ++j) {
            auto to = graph[burn][j].first,
                    len = graph[burn][j].second;
            if (dijkstra[burn] + len < dijkstra[to]) {
                dijkstra[to] = dijkstra[burn] + len;
                parents[to] = burn;
            }
        }
    }
    //return dijkstra
}

void Model::boostDijkstra() { //my BOOST dijkstra
    //distance.clear();
    //parent.clear();

    boost::dijkstra_shortest_paths(boost_graph, start_vertex,
                                   boost::predecessor_map(&parent[0]).distance_map(&distance[0]));
}

void Model::BellmanFord() { //write UR realisation here
    const unsigned CH = 1000000;
    auto startV = 0;
    std::vector<int> bellmanFord(V, CH);
    bellmanFord[startV] = 0;
    for (auto it = 0;;++it) {
        bool stop = false;
        for (auto j = 0; j < E; ++j)
            if (bellmanFord[it] < CH)
                if (bellmanFord[graph[it][j].first] >
                        bellmanFord[it] + graph[it][j].second) {
                    bellmanFord[graph[it][j].first] = bellmanFord[it] + graph[it][j].second;
                    stop = true;
                }
        if (!stop) break;
    }
}

void Model::boostBellman() { //my BOOST realisation of bellman-ford
    //distance.clear();
    //parent.clear();

    boost::bellman_ford_shortest_paths(boost_graph, start_vertex,
                                       boost::predecessor_map(&parent[0]).distance_map(&distance[0]));
}

void Model::FloydUorshell() { //??? wrire UR realisation here
    //boost::bellman_ford_shortest_paths();
    std::vector<std::vector<int>> floydUorshell(V);
    for (auto k = 0; k < V; ++k)
        for (auto i = 0; i < V; ++i)
            for (auto j = 0; j < V; ++j)
                floydUorshell[i][j] = std::min(graph[i][j].second,
                                               graph[i][k].second + graph[k][j].second);
}

void Model::boostFloyd() { //my BOOST floyd, TODO: make it works
    distance.clear();
    parent.clear();
}
