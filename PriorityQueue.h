//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/26/25.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

namespace graph {
    class PriorityQueue {
    private:
        struct Element {
            int vertex; //id
            int priority;
        };

        Element* data;
        int capacity;
        int size;

    public:
        PriorityQueue(int maxSize);
        ~PriorityQueue();

        void insert(int vertex, int priority);
        int extractMin();
        void decreaseKey(int vertex, int newPriority);
        bool isEmpty() const;
        bool contains(int vertex) const;
    };
}

#endif //PRIORITYQUEUE_H
