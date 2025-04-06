//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/26/25.
//
#include "PriorityQueue.h"
#include <limits>
#include <stdexcept>
namespace graph {
    PriorityQueue::PriorityQueue(int maxSize) {
        capacity = maxSize;
        size = 0;
        data = new Element[capacity];
    }

    PriorityQueue::~PriorityQueue() {
        delete[] data;
    }

    void PriorityQueue::insert(int vertex, int priority) {
        if (size >= capacity) {
            throw std::runtime_error("PriorityQueue overflow");
        }
        data[size++] = {vertex, priority};
    }

    int PriorityQueue::extractMin() {
        if (isEmpty()) {
            throw std::runtime_error("PriorityQueue underflow");
        }
        int minIndex = -1;
        int minPriority = std::numeric_limits<int>::max();

        for (int i = 0; i < size; ++i) {
            if (data[i].priority < minPriority) {
                minPriority = data[i].priority;
                minIndex = i;
            }
        }

        int minVertex = data[minIndex].vertex;
        data[minIndex] = data[size - 1];
        size--;
        return minVertex;
    }

    void PriorityQueue::decreaseKey(int vertex, int newPriority) {
        for (int i = 0; i < size; ++i) {
            if (data[i].vertex == vertex && data[i].priority > newPriority) {
                data[i].priority = newPriority;
                return;
            }
        }
    }

    bool PriorityQueue::isEmpty() const {
        return size == 0;
    }

    bool PriorityQueue::contains(int vertex) const {
        for (int i = 0; i < size; ++i) {
            if (data[i].vertex == vertex)
                return true;
        }
        return false;
    }
}
