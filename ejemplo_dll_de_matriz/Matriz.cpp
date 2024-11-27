#include "Matriz.h"

Matriz::Matriz(int filas, int columnas) {
    if (filas <= 0 || columnas <= 0) {
        throw std::invalid_argument("Las dimensiones deben ser mayores a cero.");
    }
    this->filas = filas;
    this->columnas = columnas;
    datos.resize(filas, std::vector<int>(columnas, 0));
}

void Matriz::validarIndices(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        throw std::out_of_range("Índice fuera de rango.");
    }
}

int Matriz::getFilas() const {
    return filas;
}

int Matriz::getColumnas() const {
    return columnas;
}

int Matriz::getElemento(int fila, int columna) const {
    validarIndices(fila, columna);
    return datos[fila][columna];
}

void Matriz::setElemento(int fila, int columna, int valor) {
    validarIndices(fila, columna);
    datos[fila][columna] = valor;
}

void Matriz::imprimir() const {
    for (const auto& fila : datos) {
        for (int valor : fila) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}

// Funciones exportadas
extern "C" {
    Matriz* crearMatriz(int filas, int columnas) {
        return new Matriz(filas, columnas);
    }

    void liberarMatriz(Matriz* matriz) {
        delete matriz;
    }
}
