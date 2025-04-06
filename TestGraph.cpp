//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/28/25.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Graph.h"
#include "doctest.h"
#include "Queue.h"
#include "Algorithms.h"
#include "PriorityQueue.h"
#include "UnionFind.h"

using namespace graph;

//helper function to check how many edges in the graph. I used it in DFS test
int countEdges(const Graph& graph) {
    int numEdges = 0;
    for (int u = 0; u < graph.getNumVertices(); ++u) {
        Neighbor* curr = graph.getNeighbors(u);
        while (curr != nullptr) {
            numEdges++;
            curr = curr->next;
        }
    }
    return numEdges;
}
TEST_CASE("Graph functionality") {
    SUBCASE("Graph construction") {
        Graph g(5);
        CHECK(g.getNumVertices() == 5);
    }

    SUBCASE("addEdge - valid and duplicate") {
        Graph g(3);
        g.addEdge(0, 1, 5);
        CHECK(g.edgeExists(0, 1));
        CHECK(g.edgeExists(1, 0));
        CHECK_THROWS_AS(g.addEdge(0, 1, 3), std::invalid_argument);
    }

    SUBCASE("addEdge - invalid indices") {
        Graph g(3);
        CHECK_THROWS_AS(g.addEdge(-1, 1, 1), std::invalid_argument);
        CHECK_THROWS_AS(g.addEdge(3, 1, 1), std::invalid_argument);
        CHECK_THROWS_AS(g.addEdge(0, -1, 1), std::invalid_argument);
        CHECK_THROWS_AS(g.addEdge(0, 3, 1), std::invalid_argument);

    }

    SUBCASE("addDirectedEdge") {
        Graph g(3);
        g.addDirectedEdge(0, 1, 5);
        CHECK(g.edgeExists(0, 1));
        CHECK_FALSE(g.edgeExists(1, 0));
    }

    SUBCASE("removeEdge") {
        Graph g(3);
        g.addEdge(0, 1, 5);
        g.removeEdge(0, 1);
        CHECK_FALSE(g.edgeExists(0, 1));
        CHECK_FALSE(g.edgeExists(1, 0));

        CHECK_THROWS_AS(g.removeEdge(0, 1), std::invalid_argument);
        CHECK_THROWS_AS(g.removeEdge(0, 0), std::invalid_argument);
    }

    SUBCASE("getNeighbors") {
        Graph g(3);
        CHECK(g.getNeighbors(0) == nullptr);

        g.addEdge(0, 1, 5);
        g.addEdge(0, 2, 3);
        Neighbor* neighbors = g.getNeighbors(0);
        CHECK(neighbors != nullptr);
    }

    SUBCASE("edgeExists") {
        Graph g(3);
        CHECK_FALSE(g.edgeExists(0, 1));
        g.addEdge(0, 1, 5);
        CHECK(g.edgeExists(0, 1));
        CHECK(g.edgeExists(1, 0));
    }

    SUBCASE("print_graph") {
        Graph g(3);
        CHECK_NOTHROW(g.print_graph());

        g.addEdge(0, 1, 5);
        CHECK_NOTHROW(g.print_graph());
    }
}

TEST_CASE("Queue") {
    Queue q(3);

    SUBCASE("Empty queue and basic enqueue/dequeue") {
        CHECK(q.isEmpty());
        CHECK_FALSE(q.isFull());
        CHECK(q.size() == 0);

        q.enqueue(114);
        CHECK_FALSE(q.isEmpty());
        CHECK(q.size() == 1);

        int val = q.dequeue();
        CHECK(val == 114);
        CHECK(q.isEmpty());
    }

    SUBCASE("Enqueue until full and check overflow") {
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        CHECK(q.isFull());
        CHECK_THROWS_AS(q.enqueue(4), std::runtime_error);
    }

    SUBCASE("Dequeue from empty queue throws exception") {
        CHECK_THROWS_AS(q.dequeue(), std::runtime_error);
    }

    SUBCASE("Queue handles circular wrapping correctly") {
        q.enqueue(1);
        q.enqueue(2);
        q.dequeue();
        q.enqueue(3);
        CHECK(q.size() == 2);
        CHECK(q.dequeue() == 2);
        CHECK(q.dequeue() == 3);
        CHECK(q.isEmpty());
    }
}
TEST_CASE("PriorityQueue") {
    PriorityQueue pq(3);

    SUBCASE("Insert elements and extractMin") {
        pq.insert(1, 10);
        pq.insert(2, 5);
        pq.insert(3, 7);
        CHECK(pq.extractMin() == 2);
        CHECK(pq.extractMin() == 3);
        CHECK(pq.extractMin() == 1);
    }

    SUBCASE("Overflow") {
        pq.insert(0, 1);
        pq.insert(1, 2);
        pq.insert(2, 3);
        CHECK_THROWS_AS(pq.insert(3, 4), std::runtime_error);
    }

    SUBCASE("Decrease key") {
        pq.insert(0, 10);
        pq.decreaseKey(0, 3);
        CHECK(pq.extractMin() == 0);
    }

    SUBCASE("Decrease key to higher value") {
        pq.insert(1, 5);
        pq.decreaseKey(1, 10);
        CHECK(pq.extractMin() == 1);
    }

    SUBCASE("Check isEmpty and contains") {
        CHECK(pq.isEmpty());
        pq.insert(5, 100);
        CHECK(pq.contains(5));
        CHECK_FALSE(pq.contains(2));
        pq.extractMin();
        CHECK(pq.isEmpty());
    }
}

TEST_CASE("UnionFind") {
    UnionFind uf(5);

    SUBCASE("Initial representatives") {
        for (int i = 0; i < 5; ++i) {
            CHECK(uf.find(i) == i);
        }
    }

    SUBCASE("Unite two sets and check representatives") {
        uf.unite(0, 1);
        int rep = uf.find(0);
        CHECK(uf.find(1) == rep);
    }

    SUBCASE("Multiple unions") {
        uf.unite(0, 1);
        uf.unite(1, 2);
        CHECK(uf.find(0) == uf.find(2));
    }
}
TEST_CASE("BFS Algorithm") {
    SUBCASE("Empty graph") {
        Graph g(0);
        CHECK_THROWS_AS(Algorithms::bfs(g, 0), std::invalid_argument);
    }

    SUBCASE("Invalid start vertex") {
        Graph g(3);
        CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::invalid_argument);
        CHECK_THROWS_AS(Algorithms::bfs(g, 3), std::invalid_argument);
    }

    SUBCASE("Single vertex") {
        Graph g(1);
        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getNumVertices() == 1);
        CHECK(bfsTree.getNeighbors(0) == nullptr);
    }

    SUBCASE("Disconnected graph") {
        Graph g(5);
        // Component 1
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        // Component 2
        g.addEdge(3, 4, 1);

        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getNumVertices() == 5);
        CHECK(bfsTree.edgeExists(0, 1));
        CHECK(bfsTree.edgeExists(1, 2));
        CHECK_FALSE(bfsTree.edgeExists(2, 1));
        CHECK_FALSE(bfsTree.edgeExists(3, 4));
    }

    SUBCASE("Fully connected graph") {
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(0, 3, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(1, 3, 1);
        g.addEdge(2, 3, 1);

        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getNumVertices() == 4);
        CHECK(bfsTree.edgeExists(0, 1));
        CHECK(bfsTree.edgeExists(0, 2));
        CHECK(bfsTree.edgeExists(0, 3));
        CHECK_FALSE(bfsTree.edgeExists(1, 2));
        CHECK_FALSE(bfsTree.edgeExists(1, 3));
        CHECK_FALSE(bfsTree.edgeExists(2, 3));
    }

    SUBCASE("Cycle graph") {
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 0, 1);

        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.edgeExists(0, 1));
        CHECK(bfsTree.edgeExists(0, 3));
    }

    SUBCASE("Graph with self-loops") {
        Graph g(2);
        g.addEdge(0, 1, 1);
        CHECK_THROWS_AS(g.addEdge(0, 0, 1), std::invalid_argument);
    }
}

TEST_CASE("DFS Algorithm") {
    SUBCASE("Empty graph") {
        Graph g(0);
        CHECK_THROWS_AS(Algorithms::dfs(g, 0), std::invalid_argument);
    }

    SUBCASE("Single vertex") {
        Graph g(1);
        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 1);
        CHECK(dfsTree.getNeighbors(0) == nullptr);
        CHECK(countEdges(dfsTree) == 0);
    }

    SUBCASE("Disconnected graph") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(3, 4, 1);

        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 5);
        // Component 1
        CHECK(dfsTree.edgeExists(0, 1));
        CHECK(dfsTree.edgeExists(1, 2));
        // Component 2
        CHECK(dfsTree.edgeExists(3, 4));
    }

    SUBCASE("Long chain graph") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 4, 1);

        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 5);
        CHECK(dfsTree.edgeExists(0, 1));
        CHECK(dfsTree.edgeExists(1, 2));
        CHECK(dfsTree.edgeExists(2, 3));
        CHECK(dfsTree.edgeExists(3, 4));
    }
    SUBCASE("Graph with only isolated vertices") {
        Graph g(3);
        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 3);
        CHECK(countEdges(dfsTree) == 0);
    }
    SUBCASE("Invalid start vertex") {
        Graph g(3);
        CHECK_THROWS_AS(Algorithms::dfs(g, -1), std::invalid_argument);
        CHECK_THROWS_AS(Algorithms::dfs(g, 3), std::invalid_argument);
    }
    SUBCASE("DFS tree has exactly n-1 edges in connected graph") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 0, 1);
        g.addEdge(1, 3, 1);
        g.addEdge(3, 4, 1);

        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 5);

        int edgeCount = countEdges(dfsTree);
        CHECK(edgeCount == 4);
    }
    SUBCASE("DFS on disconnected graph creates forest") {
        Graph g(6);
        g.addEdge(0, 1, 1);
        g.addEdge(2, 3, 1);
        g.addEdge(4, 5, 1);

        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 6);

        int edgeCount = countEdges(dfsTree);
        CHECK(edgeCount < 5);
    }

}
TEST_CASE("Dijkstra Algorithm") {
    SUBCASE("Empty graph") {
        Graph g(0);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
    }

    SUBCASE("Graph with negative weights (invalid in dijkstra)") {
        Graph g(3);
        g.addEdge(0, 1, -5);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
    }

    SUBCASE("Unreachable vertices") {
        Graph g(3);
        g.addEdge(0, 1, 1);
        Graph dijkstraTree = Algorithms::dijkstra(g, 0);
        CHECK(dijkstraTree.getNumVertices() == 3);
        CHECK(dijkstraTree.edgeExists(0, 1));
        CHECK(dijkstraTree.getNeighbors(2) == nullptr);
    }

    SUBCASE("Simple graph with positive weights") {
        Graph g(3);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 4);
        g.addEdge(1, 2, 2);

        Graph dijkstraTree = Algorithms::dijkstra(g, 0);
        CHECK(dijkstraTree.getNumVertices() == 3);
        CHECK(dijkstraTree.edgeExists(0, 1));
        CHECK(dijkstraTree.edgeExists(1, 2));
        CHECK_FALSE(dijkstraTree.edgeExists(0, 2));
    }
}
TEST_CASE("Prim Algorithm") {
    SUBCASE("Empty graph") {
        Graph g(0);
        CHECK_THROWS_AS(Algorithms::prim(g), std::invalid_argument);
    }

    SUBCASE("Graph with negative weights") {
        Graph g(3);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, -1);
        g.addEdge(0, 2, 2);

        Graph mst = Algorithms::prim(g);
        CHECK(mst.getNumVertices() == 3);
        CHECK(mst.edgeExists(0, 1));
        CHECK(mst.edgeExists(1, 2));
        CHECK_FALSE(mst.edgeExists(0, 2));

        // Use helper function to check number of undirected edges = n - 1
        int edgeCount = countEdges(mst);
        CHECK(edgeCount / 2 == 2);
    }
}
TEST_CASE("Kruskal Algorithm") {
    SUBCASE("Empty graph") {
        Graph g(0);
        CHECK_THROWS_AS(Algorithms::kruskal(g), std::invalid_argument);
    }

    SUBCASE("Graph with same-weight edges") {
        Graph g(3);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(0, 2, 1);

        Graph mst = Algorithms::kruskal(g);
        CHECK(mst.getNumVertices() == 3);
        int edgeCount = countEdges(mst);
        CHECK(edgeCount / 2 == 2);
    }
}
TEST_CASE("Graph for All Algorithms") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 0, 3);
    g.addEdge(1, 3, 4);
    g.addEdge(3, 4, -1);

    SUBCASE("BFS") {
        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getNumVertices() == 5);
        CHECK(bfsTree.edgeExists(0, 1));
        CHECK(bfsTree.edgeExists(0, 2));
        CHECK(bfsTree.edgeExists(1, 3));
        CHECK(bfsTree.edgeExists(3, 4));
        CHECK_FALSE(bfsTree.edgeExists(2, 0));
    }

    SUBCASE("DFS") {
        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getNumVertices() == 5);
        int edgeCount = countEdges(dfsTree);
        CHECK(edgeCount == 4);

    }

    SUBCASE("Dijkstra") {
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
    }

    SUBCASE("Prim") {
        Graph mst = Algorithms::prim(g);
        CHECK(mst.getNumVertices() == 5);
        CHECK(mst.edgeExists(0, 1));
        CHECK(mst.edgeExists(1, 2));
        CHECK(mst.edgeExists(1, 3));
        CHECK(mst.edgeExists(3, 4));
        CHECK_FALSE(mst.edgeExists(2, 0));
        int numEdges = countEdges(mst);
        CHECK(numEdges / 2 == 4);
    }

    SUBCASE("Kruskal") {
        Graph mst = Algorithms::kruskal(g);
        CHECK(mst.getNumVertices() == 5);
        CHECK(mst.edgeExists(3, 4));
        CHECK(mst.edgeExists(0, 1));
        CHECK(mst.edgeExists(1, 2));
        CHECK(mst.edgeExists(1, 3));
        CHECK_FALSE(mst.edgeExists(2, 0));
        int numEdges = countEdges(mst);
        CHECK(numEdges / 2 == 4);
    }
}