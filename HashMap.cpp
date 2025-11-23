#include "HashMap.h"
#include <string>

// DJB2
unsigned long HashMap::hash_function(std::string key) {
    unsigned long hash = 5381;
    for (int i = 0; i < key.length(); i++) {
        hash = ((hash << 5) + hash) + key[i]; 
    }
    return hash;
}   

// Constructor
HashMap::HashMap(int initial_capacity) {
    this->capacity = initial_capacity;
    this->size = 0;
    this->table = new HashNode*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

// Destructor
HashMap::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        HashNode* entry = table[i];

        while (entry != nullptr) {
            HashNode* prev = entry;
            entry = entry->next;
            delete prev;
        }
    }

    delete[] table;
}

// Insertar-actualizar
void HashMap::put(std::string key, int value) {

    unsigned long hash = hash_function(key);
    int index = hash % capacity;

    // Ir al bucket
    HashNode* entry = table[index];
    HashNode* prev = nullptr;

    while (entry != nullptr) {
        if (entry->key == key) {
            entry->value = value;// Actualizar valor
            return;
        }
        prev = entry;
        entry = entry->next;
    }

    HashNode* new_node = new HashNode(key, value);// Si no existe se crea
    this->size++;

    if (prev == nullptr) {
        table[index] = new_node;
    } else {
        prev->next = new_node;
    }
}

// Conseguir val
int HashMap::get(std::string key) {
    
    unsigned long hash = hash_function(key);
    int index = hash % capacity;

    HashNode* entry = table[index];

    while (entry != nullptr) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }

    return 0;
}

// Eliminar
void HashMap::remove(std::string key) {
    
    unsigned long hash = hash_function(key);
    int index = hash % capacity;

    HashNode* entry = table[index];
    HashNode* prev = nullptr;

    while (entry != nullptr) {
        if (entry->key == key) {
            if (prev == nullptr) {
                table[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            
            delete entry; 
            this->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}