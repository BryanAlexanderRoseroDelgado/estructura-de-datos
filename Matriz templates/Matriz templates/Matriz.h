#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
#include <vector>

template <typename T>
class Matriz {
private:
    std::vector<std::vector<T>> matriz;
    int filas;
    int columnas;

public:
    // Constructor
    Matriz(int f, int c);

    // Métodos de acceso/modificación
    T getValor(int fila, int columna) const;
    void setValor(int fila, int columna, T valor);

    // Métodos para sumar matrices
    Matriz<T> suma(const Matriz<T>& otraMatriz) const;

    // Método para imprimir la matriz
    void imprimir() const;
};

#endif // MATRIZ_H
