/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Enunciado del problema: Recursividad mutua
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Recursividad Mutua: Verificacion de pariedad
#include <iostream>
using namespace std;

bool esPar(int n);
bool esImpar(int n);

bool esPar(int n) {
    if (n == 0) return true;  // Caso base: 0 es par
    return esImpar(n - 1);  // Recursion mutua: Llama a esImpar
}

bool esImpar(int n) {
    if (n == 0) return false;  // Caso base: 0 no es impar
    return esPar(n - 1);  // Recursion mutua: Llama a esPar
}

int main() {
    int numero ;
    cout <<"ingrese un numero: "<<endl;
    cin >> numero;
    cout << numero << " es " << (esPar(numero) ? "par" : "impar") << endl;
    return 0;
}

