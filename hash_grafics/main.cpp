#include <iostream>
#include "TablaHash.cpp"
#include <limits>
#include <bitset>
#include <graphics.h> // Incluir la librería graphics
#include <algorithm> // Incluir la librería algorithm para std::sort

void dibujarTabla() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)""); // Corregir la conversión de tipo

    // Aumentar el tamaño de la ventana gráfica
    int width = 800;
    int height = 600;
    initwindow(width, height);

    // Dibujar el rectángulo largo partido en posiciones
    for (int i = 0; i < 13; ++i) {
        rectangle(50 + i * 50, 50, 100 + i * 50, 100);
        outtextxy(70 + i * 50, 60, (char*)std::to_string(i).c_str()); // Corregir la conversión de tipo
    }
}

void dibujarLinea(int posicion, const std::vector<std::string>& textos) {
    int yOffset = 0;
    for (const auto& texto : textos) {
        // Dibujar una línea que una un rectángulo pequeño sobre la posición correspondiente
        line(75 + posicion * 50, 100 + yOffset, 75 + posicion * 50, 150 + yOffset);
        rectangle(50 + posicion * 50, 150 + yOffset, 100 + posicion * 50, 200 + yOffset);
        outtextxy(70 + posicion * 50, 160 + yOffset, (char*)texto.c_str()); // Imprimir el texto en lugar de la posición
        yOffset += 60; // Incrementar el offset vertical para el siguiente cuadro
    }
}

void menuNumeros() {
    TablaHash<int> tabla(13);
    int numero;
    char opcion;

    dibujarTabla(); // Dibujar la tabla al inicio

    do {
        std::cout << "Ingrese un numero entero positivo: ";
        while (!(std::cin >> numero) || numero < 0 || std::cin.fail() || std::cin.peek() != '\n') {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Entrada no valida. Ingrese un numero entero positivo: ";
        }

        int posicion = tabla.hashFunction(numero);
        tabla.insertar(numero);

        // Obtener todos los elementos en la posición y ordenarlos
        std::vector<int> elementos = tabla.obtenerElementos(posicion);
        std::sort(elementos.begin(), elementos.end());

        // Convertir los elementos a string para dibujarlos
        std::vector<std::string> textos;
        for (const auto& elem : elementos) {
            textos.push_back(std::to_string(elem));
        }

        std::cout << "Numero " << numero << " guardado en la posicion " << posicion << " de la tabla hash.\n";
        dibujarLinea(posicion, textos); // Dibujar la línea correspondiente con los números

        do {
            std::cout << "Desea ingresar otro numero? (s/n): ";
            std::cin >> opcion;
            opcion = std::tolower(opcion);
        } while (opcion != 's' && opcion != 'n');
    } while (opcion == 's');
}

void menuCadenas() {
    TablaHash<std::string> tabla(13);
    std::string cadena;
    char opcion;

    dibujarTabla(); // Dibujar la tabla al inicio

    do {
        bool esValida;
        do {
            std::cout << "Ingrese una cadena de caracteres (solo letras): ";
            std::cin >> cadena;

            esValida = true;

            if (!esValida) {
                std::cout << "Cadena no valida. Ingrese una cadena de caracteres (solo letras): ";
            }
        } while (!esValida);

        int posicion = tabla.hashFunction(cadena);
        tabla.insertar(cadena);

        // Obtener todos los elementos en la posición y ordenarlos
        std::vector<std::string> elementos = tabla.obtenerElementos(posicion);
        std::sort(elementos.begin(), elementos.end());

        std::cout << "Cadena '" << cadena << "' guardada en la posicion " << posicion << " de la tabla hash.\n" << std::endl;
        dibujarLinea(posicion, elementos); // Dibujar la línea correspondiente con las cadenas

        do {
            std::cout << "Desea ingresar otra cadena? (s/n): ";
            std::cin >> opcion;
            opcion = std::tolower(opcion);
        } while (opcion != 's' && opcion != 'n');
        std::cout << std::endl;
    } while (opcion == 's');
}

int main() {
    int opcion;
    do {
        std::cout << "Seleccione el tipo de datos:\n";
        std::cout << "1. Numeros\n";
        std::cout << "2. Cadenas de caracteres\n";
        std::cout << "3. Salir\n";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                menuNumeros();
                break;
            case 2:
                menuCadenas();
                break;
            case 3:
                std::cout << "Saliendo...\n";
                closegraph(); // Cerrar la ventana gráfica al salir
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 3);

    return 0;
}