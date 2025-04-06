//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/23/25.
//
#include "Queue.h"
#include "Graph.h"
#include "Algorithms.h"
#include <limits>
#include "PriorityQueue.h"
#include "UnionFind.h"
namespace graph {

    //BFS Algorithm
    Graph Algorithms:: bfs(const Graph& graph, int start) {
        int numVertices = graph.getNumVertices();
        if (numVertices==0) {
            throw std::invalid_argument("Graph is empty.");
        }
        if (start < 0 || start >= numVertices) {
            throw std::invalid_argument("Start vertex is out of bounds.");
        }
        Graph bfsTree(numVertices);
        Queue queue(numVertices);
        bool* visited = new bool[numVertices]();
        visited[start] = true;
        queue.enqueue(start);
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            Neighbor* current =graph.getNeighbors(v);
            while (current != nullptr) {
                int u = current->id;
                if (!visited[u]) {
                    visited[u] = true;
                    bfsTree.addDirectedEdge(v, u, current->weight);
                    queue.enqueue(u);
                }
                current = current->next;

            }
        }
        delete[] visited;
        return bfsTree;
    }



    //DFS Algorithm
    Graph Algorithms:: dfs(const Graph& graph, int start) {
        int numVertices = graph.getNumVertices();
        if (numVertices==0) {
            throw std::invalid_argument("Graph is empty.");
        }
        if (start < 0 || start >= numVertices) {
            throw std::invalid_argument("Start vertex is out of bounds.");
        }
        Graph dfsTree(numVertices);
        bool* visited = new bool[numVertices]();
        // First search from the start vertex component
        dfs_visit(graph, start, visited, dfsTree);

        // Then search remaining unvisited vertices (for disconnected graph)
        for (int i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                dfs_visit(graph, i, visited, dfsTree);
            }
        }
        delete[] visited;
        return dfsTree;


    }

    //DFS visit- Recursive helper function for DFS
    void Algorithms::dfs_visit(const Graph& graph, int v, bool* visited, Graph& tree) {
        visited[v] = true;
        Neighbor* neighbor = graph.getNeighbors(v);

        while (neighbor != nullptr) {
            int u = neighbor->id;
            if (!visited[u]) {
                tree.addDirectedEdge(v, u, neighbor->weight);
                dfs_visit(graph, u, visited, tree);
            }
            neighbor = neighbor->next;
        }
    }


//Dijkstra Algorithm
    Graph Algorithms::dijkstra(const Graph& graph, int start) {
        int numVertices = graph.getNumVertices();
        if (numVertices==0) {
            throw std::invalid_argument("Graph is empty.");
        }
        if (start < 0 || start >= numVertices) {
            throw std::invalid_argument("Start vertex is out of bounds.");
        }
        Graph shortestPathsTree(numVertices);

        // Create a distance array and initialize it to infinity
        int* dist = new int[numVertices];
        int* parent = new int[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            dist[i] = std::numeric_limits<int>::max();
            parent[i] = -1;
        }
        dist[start] = 0;


        PriorityQueue pQueue(numVertices);
        pQueue.insert(start, 0);

        while (!pQueue.isEmpty()) {
            int u = pQueue.extractMin();

            Neighbor* current = graph.getNeighbors(u);
            while (current != nullptr) {
                int v = current->id;
                int weight = current->weight;
                if (weight < 0) {
                    // free memory before throwing error
                    delete[] dist;
                    delete[] parent;
                    throw std::invalid_argument("Dijkstra does not support negative edge weights.");
                }
                // relax
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;

                    if (pQueue.contains(v)) {
                        pQueue.decreaseKey(v, dist[v]);
                    } else {
                        pQueue.insert(v, dist[v]);
                    }
                }
                current = current->next;
            }
        }
        // Build the shortest path tree from parent[]
        for (int v = 0; v < numVertices; ++v) {
            if (parent[v] != -1) {
                Neighbor* current = graph.getNeighbors(parent[v]);
                while (current != nullptr) {
                    if (current->id == v) {
                        shortestPathsTree.addDirectedEdge(parent[v], v, current->weight);
                        break;
                    }
                    current = current->next;
                }
            }
        }
        delete[] dist;
        delete[] parent;
        return shortestPathsTree;
    }


//Prim Algorithm
    Graph Algorithms::prim(const Graph& graph) {
        int numVertices = graph.getNumVertices();
        if (numVertices==0) {
            throw std::invalid_argument("Graph is empty.");
        }
        Graph mst(numVertices);

        bool* inMST = new bool[numVertices]();
        int* key = new int[numVertices];
        int* parent = new int[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            key[i] = std::numeric_limits<int>::max();
            parent[i] = -1;
        }
        int start =0;
        key[0] = 0;
        PriorityQueue pQueue(numVertices);
        pQueue.insert(start, 0);

        while (!pQueue.isEmpty()) {
            int u = pQueue.extractMin();
            if (key[u] == std::numeric_limits<int>::max()) {
                continue;
            }
            inMST[u] = true;
            Neighbor* current = graph.getNeighbors(u);
            while (current != nullptr) {
                int v = current->id;
                int weight = current->weight;
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    if (pQueue.contains(v)) {
                        pQueue.decreaseKey(v, weight);
                    } else {
                        pQueue.insert(v, weight);
                    }
                }

                current = current->next;
            }
        }
        // Add selected edges to MST
        for (int v = 0; v < numVertices; ++v) {
            int u = parent[v];
            if (u != -1) {
                Neighbor* current = graph.getNeighbors(u);
                while (current != nullptr) {
                    if (current->id == v) {
                        mst.addEdge(u, v, current->weight);
                        break;
                    }
                    current = current->next;
                }
            }
        }

        delete[] inMST;
        delete[] key;
        delete[] parent;
        return mst;
    }

    // KRUSKAL Algorithm
    Graph Algorithms::kruskal(const Graph& graph) {
        int numVertices = graph.getNumVertices();
        if (numVertices == 0) {
            throw std::invalid_argument("Graph is empty.");
        }

        Graph mst(numVertices);
        UnionFind uf(numVertices);

        int edgeCount = 0;
        Edge* edges = buildEdgeArray(graph, edgeCount);
        // Sort edges by weight
        bubbleSortEdges(edges, edgeCount);

        for (int i = 0; i < edgeCount; ++i) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].weight;

            if (uf.find(u) != uf.find(v)) {
                uf.unite(u, v);
                mst.addEdge(u, v, w);
            }
        }

        delete[] edges;
        return mst;
    }

    // Makes a list of all edges in the graph without repeating any edge.
    Edge* buildEdgeArray(const Graph& graph, int& edgeCount) {
        int numVertices = graph.getNumVertices();
        Edge* edges = new Edge[numVertices * numVertices];
        edgeCount = 0;

        for (int u = 0; u < numVertices; ++u) {
            Neighbor* curr = graph.getNeighbors(u);
            while (curr != nullptr) {
                int v = curr->id;
                int w = curr->weight;
                if (u < v) {
                    edges[edgeCount++] = {u, v, w};
                }
                curr = curr->next;
            }
        }

        return edges;
    }

    //Bubble Sort
    void bubbleSortEdges(Edge* edges, int count) {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (edges[j].weight > edges[j + 1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
}
