/*************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Autor.cpp
#include "Autor.h"
#include <iomanip> // Para std::put_time
#include <sstream> // Para std::ostringstream

Autor::Autor() 
    : nombre(""), apellido(""), segundo_nombre(""), 
      segundo_apellido(""), nacionalidad("") {
    // Inicializar fecha_nacimiento a 01/01/1900
    fecha_nacimiento.tm_year = 0;  // Año 1900
    fecha_nacimiento.tm_mon = 0;   // Enero
    fecha_nacimiento.tm_mday = 1; // Día 1
}

void Autor::set_nombre(const std::string& nombre) {
    this->nombre = nombre;
}

std::string Autor::get_nombre() const {
    return nombre;
}

void Autor::set_apellido(const std::string& apellido) {
    this->apellido = apellido;
}

std::string Autor::get_apellido() const {
    return apellido;
}

void Autor::set_segundo_nombre(const std::string& segundo_nombre) {
    this->segundo_nombre = segundo_nombre;
}

std::string Autor::get_segundo_nombre() const {
    return segundo_nombre;
}

void Autor::set_segundo_apellido(const std::string& segundo_apellido) {
    this->segundo_apellido = segundo_apellido;
}

std::string Autor::get_segundo_apellido() const {
    return segundo_apellido;
}

void Autor::set_nacionalidad(const std::string& nacionalidad) {
    this->nacionalidad = nacionalidad;
}

std::string Autor::get_nacionalidad() const {
    return nacionalidad;
}

void Autor::set_fecha_nacimiento(const tm& fecha_nacimiento) {
    this->fecha_nacimiento = fecha_nacimiento;
}

tm Autor::get_fecha_nacimiento() const {
    return fecha_nacimiento;
}

std::string Autor::get_fecha_nacimiento_str() const {
    std::ostringstream oss;
    oss << std::put_time(&fecha_nacimiento, "%Y-%m-%d");
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Autor& autor) {
    os << autor.nombre << ","
       << autor.apellido << ","
       << autor.segundo_nombre << ","
       << autor.segundo_apellido << ","
       << autor.nacionalidad << ","
       << autor.get_fecha_nacimiento_str();
    return os;
}

std::istream& operator>>(std::istream& is, Autor& autor) {
    std::string nombre, apellido, segundo_nombre, segundo_apellido, nacionalidad;
    std::string fecha_str;
    tm fecha = {};

    if (std::getline(is, nombre, ',') &&
        std::getline(is, apellido, ',') &&
        std::getline(is, segundo_nombre, ',') &&
        std::getline(is, segundo_apellido, ',') &&
        std::getline(is, nacionalidad, ',') &&
        std::getline(is, fecha_str)) {

        std::istringstream iss(fecha_str);
        iss >> std::get_time(&fecha, "%Y-%m-%d"); // Parsear fecha en formato YYYY-MM-DD

        autor.set_nombre(nombre);
        autor.set_apellido(apellido);
        autor.set_segundo_nombre(segundo_nombre);
        autor.set_segundo_apellido(segundo_apellido);
        autor.set_nacionalidad(nacionalidad);
        autor.set_fecha_nacimiento(fecha);
    }

    return is;
}

