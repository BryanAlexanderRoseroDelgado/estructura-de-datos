/*************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Autor.h
#ifndef AUTOR_H
#define AUTOR_H

#include <iostream>
#include <string>
#include <ctime> // Para struct tm

class Autor {
private:
    std::string nombre;
    std::string apellido;
    std::string segundo_nombre;
    std::string segundo_apellido;
    std::string nacionalidad;
    tm fecha_nacimiento; // Cambiado de std::string a tm

public:
    Autor(); // Constructor por defecto

    void set_nombre(const std::string& nombre);
    std::string get_nombre() const;

    void set_apellido(const std::string& apellido);
    std::string get_apellido() const;

    void set_segundo_nombre(const std::string& segundo_nombre);
    std::string get_segundo_nombre() const;

    void set_segundo_apellido(const std::string& segundo_apellido);
    std::string get_segundo_apellido() const;

    void set_nacionalidad(const std::string& nacionalidad);
    std::string get_nacionalidad() const;

    void set_fecha_nacimiento(const tm& fecha_nacimiento); // Ajustado para tm
    tm get_fecha_nacimiento() const;                       // Ajustado para tm
    std::string get_fecha_nacimiento_str() const;          // Para formato legible

    // Sobrecarga de operadores
    friend std::ostream& operator<<(std::ostream& os, const Autor& autor);
    friend std::istream& operator>>(std::istream& is, Autor& autor);
};

#endif
