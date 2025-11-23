#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string> 

// Nodo para la tabla hash
struct HashNode {
    std::string key;
    int value;
    HashNode* next; // Puntero por si cae aca otro dato

    HashNode(std::string k, int v) : key(k), value(v), next(nullptr) {}
};

// Clase Tabla Hash 
class HashMap {
private:
    HashNode** table; // Tabla principal.
    int capacity; // filas
    int size;     // Elementos en total

    unsigned long hash_function(std::string key);

public:

    HashMap(int initial_capacity = 10); 

    ~HashMap();

    void put(std::string key, int value); // insertar-actualizar valor

    int get(std::string key); // da el valor
    
    void remove(std::string key);

    /////////////////////////////////////
    HashNode** get_table() const { return table; }
    
    int get_capacity() const { return capacity; }
    
    int get_size() const { return size; }
};

#endif 