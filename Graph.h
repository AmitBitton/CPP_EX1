//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/23/25.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>

namespace graph {

    struct Neighbor {
        int id;
        int weight;
        Neighbor* next;

    };

    class Graph {
    private:
        int numVertices;
        Neighbor** adjacencyList;

        void addNeighbor(int from, int to, int weight);
        void removeNeighbor(int from, int to);


    public:
        Graph(int numVertices);
        ~Graph();

        void addEdge(int src, int dst, int weight = 1);
        void print_graph() const;
        void removeEdge ( int num1, int num2 );
        Neighbor* getNeighbors(int v) const;
        void addDirectedEdge(int src, int dst, int weight);
        int getNumVertices() const;
        bool edgeExists(int src, int dst) const;



    };

}

#endif //GRAPH_H
