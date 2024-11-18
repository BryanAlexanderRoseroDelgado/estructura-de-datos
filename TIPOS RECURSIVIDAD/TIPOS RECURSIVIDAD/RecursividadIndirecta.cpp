/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Recursividad Indirecta:Secuencia de llamadas
#include <iostream>
using namespace std;

void funcionA(int n);
void funcionB(int n);
void funcionC(int n);

void funcionA(int n) {
    if (n <= 0) return;
    cout << "En funcionA con n = " << n << endl;
    funcionB(n - 1);  // Llamada recursiva a funcionB
}

void funcionB(int n) {
    if (n <= 0) return;
    cout << "En funcionB con n = " << n << endl;
    funcionC(n - 2);  // Llamada recursiva a funcionC
}

void funcionC(int n) {
    if (n <= 0) return;
    cout << "En funcionC con n = " << n << endl;
    funcionA(n - 3);  // Llamada recursiva a funcionA
}
 
int main() {
    int numero = 6;
    funcionA(numero);
    return 0;
}

