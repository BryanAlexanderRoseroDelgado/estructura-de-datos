/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Recursividad de No cola: Suma de d�gitos
#include <iostream>
using namespace std;

// Función recursiva para calcular el factorial de un número
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1; // Caso base: factorial de 0 o 1 es 1
    }
    return n * factorial(n - 1); // Operación después de la llamada recursiva
}

int main() {
    int numero;

    cout << "Ingrese un número para calcular su factorial: ";
    cin >> numero;

    cout << "El factorial de "<< numero << " es: "<< factorial(numero)<<endl;

    return 0;
}