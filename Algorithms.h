//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/24/25.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"

namespace graph {

    struct Edge {
        int u, v;
        int weight;
    };

    class Algorithms {
    public:
        static Graph bfs(const Graph& g, int start);
        static Graph dfs(const Graph& g, int start);
        static Graph dijkstra(const Graph& g, int start);
        static Graph prim(const Graph& g);
        static Graph kruskal(const Graph& g);

    private:
        static void dfs_visit(const Graph& graph, int v, bool* visited, Graph& tree);
    };
    Edge* buildEdgeArray(const Graph& graph, int& edgeCount);
    void bubbleSortEdges(Edge* edges, int edgeCount);
}




#endif //ALGORITHMS_H

