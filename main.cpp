// amiteste.bitton@msmail.ariel.ac.il
//  Created by amit on 3/23/25.
//

#include "Graph.h"
#include "Algorithms.h"
#include <iostream>

using namespace graph;
//Helper function to run and print all algorithms on a given graph
void runAllAlgorithms(const Graph& g, int startVertex = 0) {
    std::cout << "\n- BFS -" << std::endl;
    try {
        Graph bfsTree = Algorithms::bfs(g, startVertex);
        bfsTree.print_graph();
    } catch (const std::exception& e) {
        std::cout << "BFS failed: " << e.what() << std::endl;
    }

    std::cout << "\n- DFS -" << std::endl;
    try {
        Graph dfsTree = Algorithms::dfs(g, startVertex);
        dfsTree.print_graph();
    } catch (const std::exception& e) {
        std::cout << "DFS failed: " << e.what() << std::endl;
    }

    std::cout << "\n- Dijkstra -" << std::endl;
    try {
        Graph dijkstraTree = Algorithms::dijkstra(g, startVertex);
        dijkstraTree.print_graph();
    } catch (const std::exception& e) {
        std::cout << "Dijkstra failed: " << e.what() << std::endl;
    }

    std::cout << "\n- Prim -" << std::endl;
    try {
        Graph primTree = Algorithms::prim(g);
        primTree.print_graph();
    } catch (const std::exception& e) {
        std::cout << "Prim failed: " << e.what() << std::endl;
    }

    std::cout << "\n- Kruskal -" << std::endl;
    try {
        Graph kruskalTree = Algorithms::kruskal(g);
        kruskalTree.print_graph();
    } catch (const std::exception& e) {
        std::cout << "Kruskal failed: " << e.what() << std::endl;
    }
}

int main() {

    // Graph 1 – connected and simple
    Graph g1(5);
    g1.addEdge(0, 1, 1);
    g1.addEdge(1, 2, 2);
    g1.addEdge(2, 3, 3);
    g1.addEdge(3, 4, 4);
    std::cout << "- Graph 1: Simple connected graph -" << std::endl;
    g1.print_graph();
    runAllAlgorithms(g1, 0);

    // Graph 2 – with negative weight
    Graph g2(4);
    g2.addEdge(0, 1, 3);
    g2.addEdge(1, 2, -2);
    g2.addEdge(0,2,8);
    g2.addEdge(2, 3, 1);
    std::cout << "\n- Graph 2: Contains negative weight-" << std::endl;
    g2.print_graph();
    runAllAlgorithms(g2, 0);

    // Graph 3 – disconnected
    Graph g3(6);
    g3.addEdge(0, 1, 1);
    g3.addEdge(2, 3, 2);
    g3.addEdge(4, 5, 3);
    std::cout << "\n-Graph 3: Disconnected graph -" << std::endl;
    g3.print_graph();
    runAllAlgorithms(g3, 0);

    // Graph 4 – cyclic graph
    Graph g4(5);
    g4.addEdge(0, 1, 1);
    g4.addEdge(1, 2, 2);
    g4.addEdge(2, 3, 3);
    g4.addEdge(3, 0, 4);
    g4.addEdge(3, 4, 5);
    std::cout << "\n-Graph 4: Graph with a cycle -" << std::endl;
    g4.print_graph();
    runAllAlgorithms(g4, 0);

    return 0;
}