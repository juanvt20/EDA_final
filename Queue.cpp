#include "Queue.h"

Queue::Queue() {
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

Queue::~Queue() {
    QueueNode* current = this->head;
    while (current != nullptr) {
        QueueNode* next = current->next;
        delete current->Phashmap; 
        delete current;
        current = next;
    }
}

// Añadir al final
void Queue::push_back(HashMap* map) {
    
    QueueNode* new_node = new QueueNode(map);

    if (is_empty()) {
        this->head = new_node;
        this->tail = new_node;
    } else {
        this->tail->next = new_node;
        new_node->prev = this->tail;
        this->tail = new_node;
    }
    this->size++;
}

// Eliminar el primero
HashMap* Queue::pop_front() {
    if (is_empty()) {
        return nullptr;
    }

    QueueNode* deletenode = this->head;
    
    HashMap* mapreturn = deletenode->Phashmap;

    // Actualizar head
    this->head = this->head->next;

    if (this->head != nullptr) {
        this->head->prev = nullptr;
    } else {
        this->tail = nullptr;
    }

    delete deletenode;
    this->size--;

    return mapreturn;
}

int Queue::get_size() const {
    return this->size;
}

bool Queue::is_empty() const {
    return this->size == 0;

}
