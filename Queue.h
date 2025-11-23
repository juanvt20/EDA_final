#ifndef QUEUE_H
#define QUEUE_H

#include "HashMap.h" 

// Nodo para el queue
struct QueueNode {
    HashMap* topicsMap;
    QueueNode* next;
    QueueNode* prev;

    QueueNode(HashMap* map) : topicsMap(map), next(nullptr), prev(nullptr) {}
};

// Clase queue
class Queue {
private:
    QueueNode* head;
    QueueNode* tail;
    int size;

public:

    Queue();

    ~Queue();

    void push_back(HashMap* map);

    HashMap* pop_front();
    
    ///////////////////////////////
    int get_size() const;

    bool is_empty() const;
};

#endif // QUEUE_H