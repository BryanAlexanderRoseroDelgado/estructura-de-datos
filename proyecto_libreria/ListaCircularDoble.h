/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//ListaCircularDoble.h
#ifndef LISTACIRCULARDOBLE_H
#define LISTACIRCULARDOBLE_H

#include <iostream>
#include "Nodo.h"
#include <ctime> 

template <typename T>
class ListaCircularDoble{
private:
    Nodo<T>* cabeza;

public:
    ListaCircularDoble();
    ~ListaCircularDoble();

    void insertar(const T& elemento);
    void eliminar(const int& opcion, const std::string& criterioA, const std::string& criterioB);
    void eliminar_autor(const std::string& nombreAutor, const std::string& apellidoAutor);
    void buscar(const int& opcion, const std::string& criterioA, const std::string& criterioB) const;
    void buscar_autor(const std::string& nombreAutor, const std::string& apellidoAutor) const;
    void mostrar() const;
    void mostrar_autor() const;
    void limpiar();
    void verificar_INSB(std::string& insb) const;

    template <typename U>
    void validar_autor(const std::string& criterioA, const std::string& criterioB, ListaCircularDoble<U>& listaRelacionada);
    
    Nodo<T>* getCabeza() const;

// Función para buscar libros entre dos fechas
    void buscar_por_fecha(const int fechaInicio, const int fechaFin) const;
    
    // Funciones para manejo de archivos
    void guardarEnArchivo(const std::string& nombreArchivo) const;
    void cargarDesdeArchivo(const std::string& nombreArchivo);

    //Manejo del repsaldo
    void guardarRespaldo() const;
    void restaurarRespaldo();
    

};

#endif
