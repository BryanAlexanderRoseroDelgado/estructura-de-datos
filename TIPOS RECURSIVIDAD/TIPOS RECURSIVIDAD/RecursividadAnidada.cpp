/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado
 * FECHA CREACION: Lunes,  11 de noviembre de 2024
 * FECHA MODIFICACION: Domingo,  17 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Recursividad Anidada: Suma de elementos de un arreglo
#include <iostream>
using namespace std;

// Función de Ackermann recursiva
int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    }
    else if (m > 0 && n > 0) {
        return ackermann(m - 1, ackermann(m, n - 1));  // Llamada recursiva anidada
    }
    return 0; // Solo por seguridad, aunque nunca se alcanzará
}

int main() {
    int m, n;
    cout << "Introduce los valores de m y n para la función de Ackermann: ";
    cin >> m >> n;
    cout << "Resultado de Ackermann(" << m << ", " << n << ") = " << ackermann(m, n) << endl;
    return 0;
}