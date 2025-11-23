#include "TopicManager.h"
#include <iostream>
#include <chrono> // Para medir el tiempo

TopicManager::TopicManager(int k) {
    this->K = k;
    this->generalTable = new HashMap(5000); // Capacidad alta
    this->windowQueue = new Queue();
}

TopicManager::~TopicManager() {
    delete generalTable;
    delete windowQueue;
}

void TopicManager::process_news(py::list words, py::list counts) {
    // Inicio chrono
    auto start = std::chrono::high_resolution_clock::now();

    int n = py::len(words); // Tamaño de la lista de Python

    HashMap* newsMap = new HashMap(n * 2); // Mapa para la noticia

    for (int i = 0; i < n; i++) {
        // Convertimos de py a c++
        std::string w = words[i].cast<std::string>();
        int c = counts[i].cast<int>();

        newsMap->put(w, c);// Guardamos

        // Actualizamos la tabla general
        int current_total = generalTable->get(w);
        generalTable->put(w, current_total + c);
    }

    windowQueue->push_back(newsMap); // Insertar a la cola

    // Eliminar si es mayor a k
    if (windowQueue->get_size() > K) {
        HashMap* oldMap = windowQueue->pop_front();
        
        if (oldMap != nullptr) {
            HashNode** table = oldMap->get_table();
            int capacity = oldMap->get_capacity();

            // Recorremos manualmente la tabla vieja
            for (int i = 0; i < capacity; i++) {
                HashNode* node = table[i];
                while (node != nullptr) {
                    std::string key = node->key;
                    int val = node->value;

                    int act_val = generalTable->get(key);
                    int new_val = act_val - val;

                    if (new_val <= 0) {
                        generalTable->remove(key);
                    } else {
                        generalTable->put(key, new_val);
                    }
                    node = node->next;
                }
            }
            delete oldMap;
        }
    }

    // Fin chrono
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Timer almacenar datos: " << duration.count() << " us" << std::endl;
}

py::dict TopicManager::get_general_table() {
    // Inicio chrono
    auto start = std::chrono::high_resolution_clock::now();

    py::dict result; // Objeto de Python

    HashNode** table = generalTable->get_table();
    int capacity = generalTable->get_capacity();

    // Recorremos tabla hash y añdir a dict
    for (int i = 0; i < capacity; i++) {
        HashNode* node = table[i];
        while (node != nullptr) {
            result[py::str(node->key)] = node->value; 
            node = node->next;
        }
    }

    // fin chrono
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Timer hacer consulta: " << duration.count() << " us" << std::endl;

    return result;
}