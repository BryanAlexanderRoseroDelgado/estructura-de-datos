/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Libro.h
#ifndef LIBRO_H
#define LIBRO_H

#include <iostream>
#include <string>
#include <ctime> // Para struct tm

class Libro {
private:
    std::string nombre_libro;
    std::string ISNB;
    std::string nombre_autor;
    std::string apellido_autor;
    tm fecha_registro; // Nuevo atributo de tipo tm

public:
    Libro(); // Constructor por defecto

    void set_nombre_libro(const std::string& nombre_libro);
    std::string get_nombre_libro() const;

    void set_ISNB(const std::string& ISNB);
    std::string get_ISNB() const;

    void set_nombre_autor(const std::string& nombre_autor);
    std::string get_nombre_autor() const;

    void set_apellido_autor(const std::string& apellido_autor);
    std::string get_apellido_autor() const;

    void set_fecha_registro(const tm& fecha_registro); // Setter para fecha_registro
    tm get_fecha_registro() const;                     // Getter para fecha_registro
    std::string get_fecha_registro_str() const;        // Fecha en formato legible

    // Sobrecarga de operadores
    friend std::ostream& operator<<(std::ostream& os, const Libro& libro);
    friend std::istream& operator>>(std::istream& is, Libro& libro);
};

#endif
