#include <pybind11/pybind11.h>
#include "TopicManager.h"

namespace py = pybind11;

PYBIND11_MODULE(eda_cpp, m) {
    py::class_<TopicManager>(m, "TopicManager")
        .def(py::init<int>())
        .def("process_news", &TopicManager::process_news)
        .def("get_general_table", &TopicManager::get_general_table);
}