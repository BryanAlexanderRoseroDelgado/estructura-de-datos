/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Validaciones.h

#ifndef VALIDARPERSONA_H
#define VALIDARPERSONA_H
#include <vector>
#include <string>
#include <ctime>


class Validaciones {
public:
    static std::string ingresar_ISNB(int dijitos);
    static bool esISBN13Valido(const std::string& isbn);
    static bool esISBN10Valido(const std::string& isbn);
    static std::string validarISBN();

    static std::string ingresar_string();
    static std::string ingresar_string2();//para ingresar segundos nombres o apellidos
    //static std::string ingresar_string3();//para ingresar nombres de libros y nacionalidades

    static int ingresar_entero(char numero);

    static char leerLetra();

    static std::tm ingresarFecha(); // Nueva función para ingresar fecha
    static void spinner(const std::string& label, int& value, int min, int max); // Spinner genérico

    //cursor
    //int mostrarMenuConCursor(const std::vector<std::string>& opciones);

    
};

#endif 