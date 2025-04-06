//amiteste.bitton@msmail.ariel.ac.il
// Created by amit on 3/23/25.
//

#ifndef QUEUE_H
#define QUEUE_H
namespace graph {
    class Queue{
    private:
        static const int MAX = 1000; // default size of the array ( for the constructor)
        int* arr;
        int front;
        int rear;
        int count; // the current size of the queue
        int capacity;

    public:
        Queue(int size = MAX);
        ~Queue();                   // destructor
        void enqueue(int value);
        int dequeue();
        int peek();
        bool isEmpty();
        bool isFull();
        int size();
    };
}
#endif //QUEUE_H
