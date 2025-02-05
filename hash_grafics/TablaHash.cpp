#include "TablaHash.h"
#include <functional>
#include <iostream>

// Constructor
template <typename T>
TablaHash<T>::TablaHash(int size) : size(size) {
    tabla.resize(size);
}

// Implementación de la función hash para cadenas
template <>
int TablaHash<std::string>::hashFunction(const std::string& key) {
    uint32_t hashValue = 0; // Inicializar el valor hash a 32 bits de ceros

    for (int i = key.length() - 1; i >= 0; --i) {
        hashValue += static_cast<uint32_t>(key[i]); // Sumar el valor ASCII del carácter actual
        //std::cout << "After adding ASCII of " << key[i] << ": " << hashValue << "\n";

        if (i > 0) { // Si hay más caracteres
            hashValue = (hashValue << 4) ^ (hashValue >> 28); // XOR shift corregido
            //std::cout << "After XOR shift: " << hashValue << "\n";
        }
    }

    //std::cout << "Final hash value before modulo: " << hashValue << "\n";
    return hashValue % size; // Devolver la posición en la tabla hash
}

// Implementación de la función hash para enteros
template <>
int TablaHash<int>::hashFunction(const int& key) {
    return key % size;
}

// Instanciación explícita de plantillas
template class TablaHash<int>;
template class TablaHash<std::string>;

// Insertar
template <typename T>
void TablaHash<T>::insertar(const T& key) {
    int index = hashFunction(key);
    tabla[index].push_back(key);
    std::cout << "Insertando '" << key << "' en posicion: " << index << std::endl;
}

// Buscar
template <typename T>
bool TablaHash<T>::buscar(const T& key) {
    int index = hashFunction(key);
    for (const auto& item : tabla[index]) {
        if (item == key) return true;
    }
    return false;
}

// Obtener elementos en una posición
template <typename T>
std::vector<T> TablaHash<T>::obtenerElementos(int posicion) {
    return tabla[posicion];
}