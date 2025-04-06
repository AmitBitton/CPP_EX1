
//amiteste.bitton@msmail.ariel.ac.il
#include "Queue.h"
#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
namespace graph {
    //constructor
    Queue::Queue(int size) {
        if (size < 0) {
            throw std::invalid_argument("Queue capacity cannot be negative");
        }
        arr = new int[size];
        front=0;
        rear=-1;
        count=0;
        capacity=size;
    }

    // Destructor
    Queue::~Queue() {
        delete[] arr;
    }

    int Queue::size() {
        return count;
    }

    bool Queue::isEmpty() {
        return (size() == 0);
    }

    bool Queue::isFull() {
        return (size() == capacity);
    }

    int Queue::dequeue()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Queue underflow");
        }

        int x = arr[front];
        front = (front + 1) % capacity;
        count--;

        return x;
    }

    void Queue::enqueue(int element)
    {
        if (isFull())
        {
            throw std::runtime_error("Queue overflow");
        }
        rear = (rear + 1) % capacity;
        arr[rear] = element;
        count++;
    }
}