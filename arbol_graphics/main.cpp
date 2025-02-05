// main.cpp
#include "ArbolTernario.cpp"
#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <cctype>

bool contieneSoloLetras(const std::string& palabra) {
    for (char c : palabra) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool esNumeroEntero(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool esLetra(char c) {
    return std::isalpha(c);
}

int main() {
    ArbolTernario arbol;
    std::string input;
    int n;

    do {
        std::cout << "Ingrese el numero de palabras: ";
        std::cin >> input;
        if (!esNumeroEntero(input)) {
            std::cout << "Por favor, ingrese un numero entero.\n";
        }
    } while (!esNumeroEntero(input));

    n = std::stoi(input);
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string palabra;
        do {
            std::cout << "Ingrese palabra " << i + 1 << " (solo letras): ";
            std::getline(std::cin, palabra);
            if (!contieneSoloLetras(palabra)) {
                std::cout << "La palabra debe contener solo letras. Intente de nuevo.\n";
            }
        } while (!contieneSoloLetras(palabra));
        arbol.insertar(palabra);
    }

    // Inicializar la ventana gráfica después de ingresar palabras
    int gd = DETECT, gm;
    char driver[] = "";
    initgraph(&gd, &gm, driver);
    initwindow(1280, 720); // Aumentar el tamaño de la ventana gráfica

    std::cout << "\nArbol actual:\n";
    arbol.graficar();
    std::cout << "\n";

    std::cout << "\nPalabras almacenadas en el arbol: " << std::endl;
    arbol.imprimir();

    // Mostrar la altura del árbol
    std::cout << "\nAltura del arbol: " << arbol.altura() << std::endl;

    // Mostrar la profundidad de una letra específica
    char letra;
    do {
        std::cout << "\nIngrese una letra para calcular su profundidad: ";
        std::cin >> letra;
        if (!esLetra(letra)) {
            std::cout << "Por favor, ingrese solo una letra.\n";
        }
    } while (!esLetra(letra));
    std::cout << "Profundidad de la letra '" << letra << "': " << arbol.profundidad(letra) << std::endl;

    // Mostrar recorridos
    std::cout << "\nRecorrido preorden: ";
    arbol.preorden();

    std::cout << "\nRecorrido posorden: ";
    arbol.posorden();

    std::cout << "\nRecorrido infijo: ";
    arbol.infijo();

    // Esperar a que el usuario cierre la ventana gráfica
    std::cout << "Presione cualquier tecla para cerrar la ventana grafica...";
    getch();

    // Cerrar la ventana gráfica
    closegraph();

    return 0;
}
