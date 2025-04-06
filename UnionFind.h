//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/26/25.
//

#ifndef UNIONFIND_H
#define UNIONFIND_H

namespace graph {
    class UnionFind {

    private:
        int* parent;
        int* rank;
        int size;

    public:
        UnionFind(int n);
        ~UnionFind();
        int find(int x);
        void unite(int x, int y);
    };
}
#endif //UNIONFIND_H
