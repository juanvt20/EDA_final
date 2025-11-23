#ifndef TOPIC_MANAGER_H
#define TOPIC_MANAGER_H

#include "HashMap.h"
#include "Queue.h"
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class TopicManager {
private:
    HashMap* generalTable;
    Queue* windowQueue;
    int K;

public:
    TopicManager(int k);
    ~TopicManager();

    // Recibimos directamente la lista de Python 
    void process_news(py::list words, py::list counts);

    // Devolvemos un diccionario de Python
    py::dict get_general_table();
};

#endif