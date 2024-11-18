/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Enunciado del problema: Recursividad simple
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Recursividad Simple: Calculo del factorial
#include <iostream>
using namespace std;

int factorial(int n) {
    if (n <= 1) return 1;  // Caso base: 0! = 1 y 1! = 1
    return n * factorial(n - 1);  // Recursion: n! = n * (n-1)!
}

int main() {
    int numero = 5;
    cout << "Factorial de " << numero << " es " << factorial(numero) << endl;
    return 0;
}

