/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Lista_Simple.h
#pragma once
#include "Nodo.h"

using namespace std;

template<typename T>
class Lista_Simple {
private:
    Nodo<T>* cabeza;
public:
    Lista_Simple();
    //void Insertar_cabeza(T);
    void Insertar_cola(T);//Crea una lista
    bool Buscar(T);//Trae todas las listas q tengan elementos en comun con uno de los nodos
    void Eliminar(T);
    void Mostrar();
    Nodo<T>* getCabeza();
};