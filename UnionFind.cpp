//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/26/25.
//
#include "UnionFind.h"
#include <stdexcept>
namespace graph {
    // Constructor – similar to the create action in Union-Find
    UnionFind::UnionFind(int n) {
        size = n;
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    //deconstructor
    UnionFind::~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int UnionFind::find(int x) {
        if (x < 0 || x >= size) throw std::out_of_range("Invalid element in UnionFind");
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void UnionFind::unite(int x, int y) {
        if (x < 0 || x >= size) throw std::out_of_range("Invalid element in UnionFind");
        if (y < 0 || y >= size) throw std::out_of_range("Invalid element in UnionFind");

        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}