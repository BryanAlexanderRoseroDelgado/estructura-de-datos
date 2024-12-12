/*************************
* UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Libro.cpp
#include "Libro.h"
#include <iomanip> // Para std::put_time
#include <sstream> // Para std::ostringstream

Libro::Libro() 
    : nombre_libro(""), ISNB(""), nombre_autor(""), apellido_autor("") {
    // Inicializar fecha_registro a 01/01/1900
    fecha_registro.tm_year = 0;  // Año 1900
    fecha_registro.tm_mon = 0;   // Enero
    fecha_registro.tm_mday = 1; // Día 1
}

void Libro::set_nombre_libro(const std::string& nombre_libro) {
    this->nombre_libro = nombre_libro;
}

std::string Libro::get_nombre_libro() const {
    return nombre_libro;
}

void Libro::set_ISNB(const std::string& ISNB) {
    this->ISNB = ISNB;
}

std::string Libro::get_ISNB() const {
    return ISNB;
}

void Libro::set_nombre_autor(const std::string& nombre_autor) {
    this->nombre_autor = nombre_autor;
}

std::string Libro::get_nombre_autor() const {
    return nombre_autor;
}

void Libro::set_apellido_autor(const std::string& apellido_autor) {
    this->apellido_autor = apellido_autor;
}

std::string Libro::get_apellido_autor() const {
    return apellido_autor;
}

void Libro::set_fecha_registro(const tm& fecha_registro) {
    this->fecha_registro = fecha_registro;
}

tm Libro::get_fecha_registro() const {
    return fecha_registro;
}

std::string Libro::get_fecha_registro_str() const {
    std::ostringstream oss;
    oss << std::put_time(&fecha_registro, "%Y-%m-%d");
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Libro& libro) {
    os << libro.get_nombre_libro() << ","
       << libro.get_ISNB() << ","
       << libro.get_nombre_autor() << ","
       << libro.get_apellido_autor() << ","
       << libro.get_fecha_registro_str(); // Agregado fecha_registro formateada
    return os;
}

std::istream& operator>>(std::istream& is, Libro& libro) {
    std::string nombreLibro, ISNB, nombreAutor, apellidoAutor, fechaStr;
    tm fecha = {};

    if (std::getline(is, nombreLibro, ',') &&
        std::getline(is, ISNB, ',') &&
        std::getline(is, nombreAutor, ',') &&
        std::getline(is, apellidoAutor, ',') &&
        std::getline(is, fechaStr)) {
        
        std::istringstream iss(fechaStr);
        iss >> std::get_time(&fecha, "%Y-%m-%d"); // Parsear fecha en formato YYYY-MM-DD

        libro.set_nombre_libro(nombreLibro);
        libro.set_ISNB(ISNB);
        libro.set_nombre_autor(nombreAutor);
        libro.set_apellido_autor(apellidoAutor);
        libro.set_fecha_registro(fecha);
    }

    return is;
}


