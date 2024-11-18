/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/

#include <iostream>
using namespace std;

// Función recursiva de cola para calcular el factorial
int factorialTail(int n, int acumulador = 1) {
    if (n == 0 || n == 1) {
        return acumulador;
    }
    // Llamada recursiva de cola
    return factorialTail(n - 1, n * acumulador);
}

// Función para que el usuario pueda ingresar un número y ver el resultado del factorial
int main() {
    int numero;
    cout << "Ingrese un número para calcular su factorial: ";
    cin >> numero;

    if (numero < 0) {
        cout << "El factorial no está definido para números negativos." << endl;
    } else {
        cout << "El factorial de " << numero << " es: " << factorialTail(numero) << endl;
    }

    return 0;
}