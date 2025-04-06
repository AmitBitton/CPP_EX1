//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/23/25.
//
// Graph.cpp

#include "Graph.h"

namespace graph {

    // constructor for the graph
    Graph::Graph(int numOfVertices) {
        if (numOfVertices<0){
        throw std::invalid_argument("Invalid number of vertices. number of vertices must be positive.");
        }
        this->numVertices = numOfVertices;
        adjacencyList = new Neighbor*[numOfVertices];

        for (int i = 0; i < numOfVertices; ++i) {
            adjacencyList[i] = nullptr;
        }
    }

    //deconstructor
    Graph::~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            Neighbor* curr = adjacencyList[i];
            while (curr != nullptr) {
                Neighbor* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] adjacencyList;
    }


    void Graph::addEdge(int src, int dst, int weight) {
        if (src < 0 || src >= numVertices || dst < 0 || dst >= numVertices) {
            throw std::invalid_argument("Invalid vertex index");
        }
        if (edgeExists(src, dst)) {
            throw std::invalid_argument("Edge already exists");
        }
        if (src == dst) {
            throw std::invalid_argument("Same vertex are not allowed - can't add edge");
        }
        addNeighbor(src, dst, weight);
        addNeighbor(dst, src, weight);
    }

    void Graph::addDirectedEdge(int src, int dst, int weight) {
        if (src < 0 || src >= numVertices || dst < 0 || dst >= numVertices) {
            throw std::invalid_argument("Invalid vertex index");
        }
        addNeighbor(src, dst, weight);
    }

    void Graph::print_graph() const {
        for (int i = 0; i < numVertices; ++i) {
            std:: cout << "Vertex " << i << ": ";
            Neighbor* curr = adjacencyList[i];
            while (curr != nullptr) {
                std:: cout << "(" << curr->id << ", weight=" << curr->weight << ") ";
                curr = curr->next;
            }
           std:: cout << std:: endl;
        }
    }


    void Graph::addNeighbor(int src, int dst, int weight) {
        Neighbor* newNeighbor = new Neighbor{dst, weight, adjacencyList[src]};
        adjacencyList[src] = newNeighbor;
    }

    void Graph::removeEdge(int src, int dst) {
        if (src < 0 || src >= numVertices || dst < 0 || dst >= numVertices) {
            throw std::invalid_argument("Invalid vertex index");
        }
        removeNeighbor(src, dst);
        removeNeighbor(dst, src);
    }


    void Graph::removeNeighbor(int src, int dst) {
        Neighbor* curr = adjacencyList[src];
        Neighbor* prev = nullptr;

        while (curr != nullptr) {
            if (curr->id == dst) {
                if (prev == nullptr) {
                    adjacencyList[src] = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        throw std::invalid_argument("Edge not found!");
    }

    Neighbor* Graph::getNeighbors(int v) const {
        return adjacencyList[v];
    }
    int Graph::getNumVertices() const {
        return numVertices;
    }
    bool Graph::edgeExists(int src, int dst) const {
        Neighbor* current = adjacencyList[src];
        while (current != nullptr) {
            if (current->id == dst) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    }

