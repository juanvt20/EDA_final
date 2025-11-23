# EDA_final

## Arquitectura de la Estructura de datos
En el siguiente proyecto se usaron 2 estructuras de datos, Tabla Hash y Queue.
Estas Estructuras de datos estan formadas de la siguiente manera
### Tabla hash
Esta Tabla Hash, primeramente esta formada de un array(Figura 2), pero este array es un array de punteros a nodos(Figura 1) dode cada nodo tiene 3 variables:key,estas son las palabras que potencialmente apareceran en la wordcloud; value, es la cantidad de veces que se repite la key y por ultimo un puntero que en caso de colisión apuntará a otro nodo. 
La tabla hash tiene un array estatico que en el TopicManager se escoge y se escoge segun se vea necesario para no tener colisiones. 
Esta tabla hash se eligió debido a que su tiempo de inserción, eliminación y consulta es de o(1) la mayoria de veces(exceto en colisiones), esto hace que sea eficiente a la hora de aplicarlo.

#### Figura 1. HashNode
![Diagrama de Arquitectura](./img/arquitectura_general.png)
#### Figura 2. HashMap
![Diagrama de Arquitectura](./img/arquitectura_general.png)
#### Figura 3. QueueNode
![Diagrama de Arquitectura](./img/arquitectura_general.png)
#### Figura 4. Queue
![Diagrama de Arquitectura](./img/arquitectura_general.png)

## Requisitos Previos

Para compilar este proyecto necesitas tener instalado:

1.  **Compilador de C++:** Compatible con C++11 o superior (G++, Clang, o MSVC).
2.  **CMake:** Versión 3.15 o superior.
3.  **Python:** Versión 3.x.
4.  **Pybind11:** Librería para conectar C++ y Python.

### Instalación de dependencias (Python)
```bash
pip install pybind11


## Arquitectura de la Estructura de datos
