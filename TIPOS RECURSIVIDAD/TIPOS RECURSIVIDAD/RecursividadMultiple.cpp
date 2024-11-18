/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Recursividad Multiple: Secuencia de Fibonacci
#include <iostream>
using namespace std;

int fibonacci(int n) {
    if (n <= 1) return n;  // Caso base: F(0) = 0, F(1) = 1
    return fibonacci(n - 1) + fibonacci(n - 2);  // Recursi�n m�ltiple
}

int main() {
    int numero;
    cout << "Ingrese un número: ";
    cin >> numero;
    cout << "Fibonacci de " << numero << " es " << fibonacci(numero) << endl;
    return 0;
}

