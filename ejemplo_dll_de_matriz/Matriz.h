#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <stdexcept>
#include <iostream>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

class DLL_EXPORT Matriz {
private:
    std::vector<std::vector<int>> datos;
    int filas;
    int columnas;

public:
    Matriz(int filas, int columnas);

    // Métodos de validación
    void validarIndices(int fila, int columna) const;

    // Métodos de acceso
    int getFilas() const;
    int getColumnas() const;
    int getElemento(int fila, int columna) const;
    void setElemento(int fila, int columna, int valor);

    // Método para imprimir la matriz
    void imprimir() const;
};

extern "C" {
    DLL_EXPORT Matriz* crearMatriz(int filas, int columnas);
    DLL_EXPORT void liberarMatriz(Matriz* matriz);
}

#endif // MATRIZ_H
