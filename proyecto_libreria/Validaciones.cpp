/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Validaciones.cpp

#include "Validaciones.h"
#include <iostream>
#include <iomanip> 
#include <cctype>
#include <conio.h>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>

std::string Validaciones::ingresar_ISNB(int dijitos) {
    std::string entrada;
    char c;
    entrada.clear(); 

    while (true) {
        c = getch(); // Leer un carácter
        if (c >= '0' && c <= '9') { 
            if (entrada.size() < dijitos) { // valida q no se ingrese mas de # digitos
                std::cout << c; 
                entrada += c; 
            }
        } else if (c == 8 && !entrada.empty()) { //permite retroceder
            std::cout << "\b \b"; 
            entrada.pop_back();   
        } else if (c == 13 && entrada.size() == dijitos) { // valida q no se ingrese menos de # digitos
            std::cout << std::endl;
            break; 
        }
    }
    return entrada;
}

    // Validación de ISBN-13
    bool Validaciones::esISBN13Valido(const std::string& isbn) {
        if (isbn.length() != 13) return false;
        
        int suma = 0;
        for (int i = 0; i < 12; ++i) {
            if (!isdigit(isbn[i])) return false;
            suma += (i % 2 == 0) ? (isbn[i] - '0') : (isbn[i] - '0') * 3;
        }
        
        int digitoControl = (10 - (suma % 10)) % 10;
        return digitoControl == (isbn[12] - '0');
    }

    // Validación de ISBN-10
    bool Validaciones::esISBN10Valido(const std::string& isbn) {
        if (isbn.length() != 10) return false;
        
        int suma = 0;
        for (int i = 0; i < 9; ++i) {
            if (!isdigit(isbn[i])) return false;
            suma += (isbn[i] - '0') * (10 - i);
        }
        
        char digitoControl = isbn[9];
        if (digitoControl == 'X') digitoControl = 10;  // 'X' representa el 10
        if (!isdigit(digitoControl) && digitoControl != 'X') return false;
        
        suma += (digitoControl == 'X') ? 10 : (digitoControl - '0');
        return suma % 11 == 0;
    }

    //ingreso validado del isbn
std::string Validaciones::validarISBN() {
    std::string isbn;
    int opcion;
    char c;

    std::cout << "¿Qué tipo de ISBN desea ingresar?\n";
    std::cout << "1. ISBN-10\n";
    std::cout << "2. ISBN-13\n";
    std::cout << "Elija una opción: ";

    while (true) {
        c = getch(); // Leer un carácter
        
        if (c >= '1' && c <= '2') {
            std::cout << c << std::endl; // Mostrar el número
            opcion = c - '0'; // Convertir de char a int
            break; // Salir del ciclo cuando la opción es válida
        } 
        else if (c == 13) { // Si se presiona Enter sin una opción válida
            std::cout << "\nOpción no válida. Intente de nuevo.\n";
        }
    }

    // Validar ISBN-10
    if (opcion == 1) {
        std::cout << "Ingrese el ISBN-10: \n";
        isbn = ingresar_ISNB(10);
        while (!esISBN10Valido(isbn)) {
            std::cout << "Error: ISBN-10 no válido. Intenta nuevamente.\n";
            isbn = ingresar_ISNB(10); // Solicitar nuevamente el ISBN-10
        }
        return isbn;
    } 
    
    // Validar ISBN-13
    else if (opcion == 2) {
        std::cout << "Ingrese el ISBN-13: \n";
        isbn = ingresar_ISNB(13);
        while (!esISBN13Valido(isbn)) {
            std::cout << "Error: ISBN-13 no válido. Intenta nuevamente.\n";
            isbn = ingresar_ISNB(13); // Solicitar nuevamente el ISBN-13
        }
        return isbn;
    }
   /* else { 
        // Manejo de opción inválida
         std::cout << "Opción no válida. Intente de nuevo.\n";
    }*/
}


std::string Validaciones::ingresar_string(){
    std::string dato;
    char c; 
    dato.clear();

    while (true) {
        c = getch();
        if (isalpha(c)) {
            std::cout << c; 
            dato += c;  
        } else if (c == 8 && !dato.empty()) { // Manejar Backspace
            std::cout << "\b \b";
            dato.pop_back();  
        } else if (c == 13) { // Detectar Enter
            if (!dato.empty()) {
                std::cout << std::endl;
                break; // Salir del bucle si hay contenido
            }
        }
    }

    // Convertir la primera letra a mayúscula
    if (!dato.empty()) {
        dato[0] = toupper(dato[0]);
    }

    return dato;
}

std::string Validaciones::ingresar_string2(){
    std::string dato;
    char c; 
    dato.clear();

    while (true) {
        c = getch();  // Leer el carácter tecleado por el usuario

        if (isalpha(c)) {  // Si el carácter es una letra
            std::cout << c; 
            dato += c;  
        } else if (c == 8 && !dato.empty()) { // Manejar Backspace
            std::cout << "\b \b";
            dato.pop_back();  
        } else if (c == 13) { // Detectar Enter
            if (dato.empty()) { // Si no se ha tecleado nada, salir con un string vacío
                std::cout << std::endl;
                break; // Salir del bucle
            } else {
                std::cout << std::endl;
                break; // Salir si hay contenido
            }
        }
    }

    // Convertir la primera letra a mayúscula, si la cadena no está vacía
    if (!dato.empty()) {
        dato[0] = toupper(dato[0]);
    }

    return dato;
}



int Validaciones::ingresar_entero(char numero){
    char c;
    while (true) {
        c = getch(); 
        
        if (c >= '1' && c <= numero) {
            std::cout << c << std::endl; // Mostrar el número
            return c - '0'; // Convertir de char a int y retornar
        } 
        else if (c == 13) {
        }
    }
}


// Spinner genérico
void Validaciones::spinner(const std::string& label, int& value, int min, int max) {
    while (true) {
        // Mostrar el valor actual con un formato claro
        std::cout << "\r" << label << ": " << std::setw(2) << std::setfill('0') << value << " ";
        std::cout.flush();

        char key = _getch(); // Capturar entrada del teclado
        if (key == 0 || key == -32) { // Detectar teclas especiales
            key = _getch(); // Obtener el código real de la tecla especial
            if (key == 72 && value < max) { // Flecha hacia arriba
                value++;
            } else if (key == 80 && value > min) { // Flecha hacia abajo
                value--;
            }
        } else if (key == '\r') { // Enter para confirmar
            break;
        }

        // Prevenir comportamiento extraño borrando la línea
        std::cout << "\r" << std::string(label.size() + 5, ' ') << "\r";
    }
    std::cout << "\n"; // Asegurar un salto de línea al finalizar
}

// Ingreso de fecha
std::tm Validaciones::ingresarFecha() {
    const int MIN_ANIO = 1900, MAX_ANIO = 2024;
    int dia = 1, mes = 1, anio = 2000;

    while (true) {
        std::cout << "Ingrese la fecha de nacimiento:\n";
        std::cout << "Use las flechas para ajustar valores, Tab para alternar y Enter para confirmar.\n\n";

        // Spinner para día
        spinner("Dia", dia, 1, 31);

        // Spinner para mes
        spinner("Mes", mes, 1, 12);

        // Ajustar días según el mes (sin considerar años bisiestos)
        int diasMaximos = (mes == 2) ? 28 : (mes == 4 || mes == 6 || mes == 9 || mes == 11) ? 30 : 31;
        if (dia > diasMaximos) dia = diasMaximos;

        // Spinner para año
        spinner("Anio", anio, MIN_ANIO, MAX_ANIO);

        // Validar fecha
        if (dia > 0 && dia <= diasMaximos) {
            std::tm fecha = {};
            fecha.tm_mday = dia;
            fecha.tm_mon = mes - 1;
            fecha.tm_year = anio - 1900;

            // Obtener la fecha actual del sistema
            std::time_t tiempoActual = std::time(nullptr);
            std::tm fechaActual = *std::localtime(&tiempoActual);

            // Comparar la fecha ingresada con la fecha actual
            std::tm fechaIngresada = fecha;
            fechaIngresada.tm_hour = 0;
            fechaIngresada.tm_min = 0;
            fechaIngresada.tm_sec = 0;

            std::time_t tiempoIngresado = std::mktime(&fechaIngresada);
            std::time_t tiempoActualComparar = std::mktime(&fechaActual);

            if (tiempoIngresado > tiempoActualComparar) {
                std::cout << "\nError: La fecha ingresada no existe aún. Intente nuevamente.\n";
                std::cout << "Presione Enter para continuar...\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Esperar Enter
                continue;
            }

            return fecha;  // Fecha válida
        }

        std::cout << "\nFecha inválida. Reingrese los valores.\n";
        std::cout << "Presione Enter para continuar...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Esperar Enter
    }
}


char Validaciones::leerLetra() {
    char c; // Carácter ingresado
    while (true) {
        c = getch(); // Captura el carácter sin mostrarlo directamente

        // Validar si es una letra (mayúscula o minúscula)
        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) {
            putchar(c); // Mostrar el carácter ingresado
            putchar('\n'); // Simular que el usuario presionó Enter después de la letra
            return c; // Retornar el carácter ingresado
        }

        // Validar si se presionó retroceso
        if (c == '\b' || c == 127) {
            putchar('\b'); // Mover cursor atrás
            putchar(' ');  // Sobrescribir el carácter anterior con un espacio
            putchar('\b'); // Mover el cursor nuevamente atrás
        }

        // Ignorar otros caracteres y continuar esperando entrada
    }
}

/*int Validaciones::mostrarMenuConCursor(const std::vector<std::string>& opciones) {
    int seleccion = 0; // Índice de la opción seleccionada
    const char cursor = '>'; // Símbolo del cursor
    const char espacio = ' '; // Espacio para opciones no seleccionadas

    while (true) {
        for (size_t i = 0; i < opciones.size(); ++i) {
            if (i == seleccion) {
                std::cout << cursor << " " << opciones[i] << std::endl;
            } else {
                std::cout << espacio << " " << opciones[i] << std::endl;
            }
        }

       std:: cout << "\nUse las teclas arriba/abajo para moverse y Enter para seleccionar.\n";

        // Captura entrada del teclado
        char tecla = _getch();

        // Control del cursor
        if (tecla == 72) { // Flecha arriba
            if (seleccion > 0) seleccion--;
        } else if (tecla == 80) { // Flecha abajo
            if (seleccion < opciones.size() - 1) seleccion++;
        } else if (tecla == 13) { // Enter
            return seleccion;
        }
    }
}*/
