# EDA_final

Este proyecto implementa un sistema de procesamiento de noticias en tiempo real utilizando una arquitectura híbrida. El núcleo de la estructura de datos (HashMaps y Queues) está escrito en **C++** para máxima eficiencia, mientras que la interfaz y la ingesta de datos se manejan desde **Python** utilizando **Pybind11**.

## Requisitos Previos

Para compilar este proyecto necesitas tener instalado:

1.  **Compilador de C++:** Compatible con C++11 o superior (G++, Clang, o MSVC).
2.  **CMake:** Versión 3.15 o superior.
3.  **Python:** Versión 3.x.
4.  **Pybind11:** Librería para conectar C++ y Python.

### Instalación de dependencias (Python)
```bash
pip install pybind11
