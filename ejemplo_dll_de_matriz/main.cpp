#include <iostream>
#include <windows.h>
#include "Matriz.h"

typedef Matriz* (*CrearMatrizFunc)(int, int);
typedef void (*LiberarMatrizFunc)(Matriz*);
typedef void (*SetElementoFunc)(Matriz*, int, int, int);
typedef int (*GetElementoFunc)(Matriz*, int, int);
typedef void (*ImprimirMatrizFunc)(Matriz*);

int main() {
    // Cargar el DLL
    HINSTANCE hDLL = LoadLibrary("Matriz.dll");
    if (!hDLL) {
        std::cerr << "No se pudo cargar el DLL." << std::endl;
        return -1;
    }

    // Obtener punteros a las funciones del DLL
    auto crearMatriz = (CrearMatrizFunc)GetProcAddress(hDLL, "crearMatriz");
    auto liberarMatriz = (LiberarMatrizFunc)GetProcAddress(hDLL, "liberarMatriz");

    if (!crearMatriz || !liberarMatriz) {
        std::cerr << "No se pudieron encontrar las funciones en el DLL." << std::endl;
        FreeLibrary(hDLL);
        return -1;
    }

    // Crear una matriz
    Matriz* matriz = crearMatriz(3, 3);

    // Modificar elementos de la matriz
    matriz->setElemento(0, 0, 10);
    matriz->setElemento(1, 1, 20);
    matriz->setElemento(2, 2, 30);

    // Imprimir la matriz
    std::cout << "Contenido de la matriz:" << std::endl;
    matriz->imprimir();

    // Liberar la matriz y el DLL
    liberarMatriz(matriz);
    FreeLibrary(hDLL);

    return 0;
}
