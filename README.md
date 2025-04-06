# Graph Algorithms Project c++

## Overview
This project implements graph algorithms using an adjacency list representation. It includes algorithms such as BFS, DFS, Dijkstra, Prim, and Kruskal. 
In accordance with the project requirements, no use of the STL was allowed.
Therefore, all data structures including the queue, priority queue, and union-find were manually implemented. 
The project including unit testing using the doctest framework and check memory leak using valgrind.

## Project Structure  
```
├── Graph.h / Graph.cpp         # Implements the graph structure using adjacency lists
├── Algorithms.h / Algorithms.cpp # Static class contains all the algorithms: BFS, DFS, Dijkstra, Prim, Kruskal
├── Queue.h / Queue.cpp         # Simple custom queue used in BFS (no STL)
├── PriorityQueue.h / .cpp      # Min-priority queue for Dijkstra and Prim
├── UnionFind.h / .cpp          # Union-Find structure for Kruskal
├── Main.cpp                    # Runs all algorithms on sample graphs as a demo
├── TestGraph.cpp               # Unit tests for all classes and algorithms using doctest
├── Makefile                    # Compilation, testing, valgrind and cleanup
└── README.md                   # Documentation for the project (this file)
```
## Classes Overview

### Graph
Represents a graph using an adjacency list  
**Used by**: All algorithms  
- Supports undirected and directed edges (`addEdge`, `addDirectedEdge`)
- Allows edge removal, printing, and existence checks
- Neighbor nodes are stored as a linked list used the `Neighbor` struct
- Throws exceptions for:
  - Invalid vertices
  - Duplicate edges
  - Self-loops

---

### Algorithms
A static class that implements the graph algorithms  
**Algorithms Included**:
- `bfs` – Breadth First Search (uses `Queue`)
- `dfs` – Depth First Search (recursive, builds a DFS tree/forest)
- `dijkstra` – Shortest path from source (non-negative weights only)
- `prim` – Minimum Spanning Tree (uses `PriorityQueue`)
- `kruskal` – Minimum Spanning Tree (uses `UnionFind` + Bubble Sort)

**Notes**:
- Each algorithm returns a new `Graph` representing the result tree/forest
- Throws `invalid_argument` on invalid inputs or bad structure
- `dfs_visit` is a private helper used by DFS

---

### Queue
Basic circular queue   
- Manually implemented using a dynamic array
- Supports: `enqueue`, `dequeue`, `isEmpty`, `isFull`, `size`
- Manages internal state manually (`front`, `rear`, `count`)
- Throws exceptions on overflow/underflow

---

### PriorityQueue
Array-based min-priority queue used in Dijkstra and Prim  
- Supports: `insert`, `extractMin`, `decreaseKey`, `contains`, `isEmpty`
- 
---

### UnionFind
Disjoint-set structure used in Kruskal's algorithm  
- Efficiently tracks components using:
  - `find` (with path compression)
  - `unite` (by rank)
- Throws on invalid input

---

### TestGraph.cpp
Unit tests using  [doctest](https://github.com/doctest/doctest). 

**Includes tests for**:
- All algorithms: `bfs`, `dfs`, `dijkstra`, `prim`, `kruskal`
- Data structures: `Graph`, `Queue`, `PriorityQueue`, `UnionFind`
- Covers:
  - Edge cases (empty graphs, invalid vertices)
  - Exception handling
  - Tree/forest correctness
  - Edge counts
  - Negative weights 

---

### main.cpp
Demo of algorithm usage  
- Creates multiple graphs:
  - Connected
  - Disconnected
  - With cycles
  - With negative weights
- Uses a helper function `runAllAlgorithms()` to reduce code repetition

---

## Running the Project

>  Make sure `clang++-18`, `make`, and `valgrind` are installed

### Compile and Run the Main Demo
```
make Main

./main
```
---
### Run the Unit Tests
This compiles and runs all tests using the doctest framework
```
make test
./test
```
---
### Run Memory Check with Valgrind
Check for memory leaks in both the demo and unit tests:
```
make valgrind
```
---
### Clean Build Files
Remove all compiled files (main, test, and .o files)
```
make clean
```
---
## Notes
+ I used the pseudo code algorithms from the [book](https://dl.ebooksworld.ir/books/Introduction.to.Algorithms.4th.Leiserson.Stein.Rivest.Cormen.MIT.Press.9780262046305.EBooksWorld.ir.pdf
) (from the course forum).
+ All memory checks using **Valgrind** passed successfully with no leaks detected.

---
# Author
+ Written by: Amit Bitton
+ Mail: amiteste.bitton@msmail.ariel.ac.il
+ Systems programming 2 , EX1, April 2025
