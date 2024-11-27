/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
#include <iostream>
#include "Matriz.cpp"
#include "Matriz.h"

int main() {
    int filas = 3, columnas = 3;

    Matriz<int> mat1(filas, columnas);
    Matriz<int> mat2(filas, columnas);

    // Llenar las matrices con valores
    std::cout << "Introduzca los valores para la primera matriz (mat1): " << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            int valor;
            std::cout << "Elemento [" << i << "][" << j << "]: ";
            std::cin >> valor;
            mat1.setValor(i, j, valor);
        }
    }

    std::cout << "Introduzca los valores para la segunda matriz (mat2): " << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            int valor;
            std::cout << "Elemento [" << i << "][" << j << "]: ";
            std::cin >> valor;
            mat2.setValor(i, j, valor);
        }
    }

    // Imprimir las matrices
    std::cout << "\nMatriz 1:" << std::endl;
    mat1.imprimir();

    std::cout << "\nMatriz 2:" << std::endl;
    mat2.imprimir();

    // Sumar las matrices
    Matriz<int> resultado = mat1.suma(mat2);

    // Imprimir la matriz resultante
    std::cout << "\nMatriz Resultante (Suma):" << std::endl;
    resultado.imprimir();

    return 0;
}
