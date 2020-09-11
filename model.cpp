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

std::pair<unsigned, unsigned long> Model::sizeGraph() {
    return std::pair<unsigned, unsigned long>{V, E};
}

void Model::generateGraph() {
    srand(time(NULL));

    auto maxWeight = 50;
    auto tmp = 0;
    for (auto it = 1; it < V; ++it) {
        graph.at(0).push_back(std::pair<int, int>{it, (rand() % maxWeight + 1)});
        graph.at(it).push_back(std::pair<int, int>{0, (rand() % maxWeight + 1)});
        ++tmp;
    }

    while (tmp != E) {
        auto u = rand() % (V - 1) + 1;
        auto v = rand() % (V - 1) + 1;
        if (u == v)
            while ( u != v)
                u = rand() % (V - 1) + 1;
        graph.at(u).push_back(std::pair<int, int>{v, (rand() % maxWeight + 1)});
        graph.at(v).push_back(std::pair<int, int>{u, (rand() % maxWeight + 1)});
        tmp++;
    }
}

void Model::Dijkstra() { //find path needed
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
}

void Model::BellmanFord() { //find path needed
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

void Model::FloydUorshell() { //??? need to find path
    std::vector<std::vector<int>> floydUorshell(V);
    for (auto k = 0; k < V; ++k)
        for (auto i = 0; i < V; ++i)
            for (auto j = 0; j < V; ++j)
                floydUorshell[i][j] = std::min(graph[i][j].second,
                                               graph[i][k].second + graph[k][j].second);
}
