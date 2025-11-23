cmake_minimum_required(VERSION 3.15)
project(eda_project)

set(CMAKE_CXX_STANDARD 11)

# Buscar Python 
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# Buscar Pybind11 
execute_process(
    COMMAND "${Python_EXECUTABLE}" -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Ruta a CMake
list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")

# Buscar paquete
find_package(pybind11 CONFIG REQUIRED)

# Modulos de c++
pybind11_add_module(eda_cpp
    bindings.cpp
    TopicManager.cpp
    HashMap.cpp
    Queue.cpp
)

# Libreria necesaria
target_link_libraries(eda_cpp PRIVATE pybind11::module)