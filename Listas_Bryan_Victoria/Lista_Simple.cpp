/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Lista_Simple.cpp

#include "Lista_Simple.h"

using namespace std;


template <typename T>
Lista_Simple<T>::Lista_Simple()
{
    cabeza = NULL;
}

/*template <typename T>
void Lista_Simple<T>::Insertar_cabeza(T _dato)
{
    Nodo<T>* nuevo = new Nodo(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}*/

template<typename T> 
 void Lista_Simple<T>::Insertar_cola(T _dato) {
    Nodo<T>* nuevo = new Nodo(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

template<typename T>
bool Lista_Simple<T>::Buscar(T _dato) {
    Nodo<T>* actual = cabeza;
    while (actual != NULL) {
        if (actual->getDato() == _dato) {
            // cout << "El dato " << _dato << " si se encuentra en la lista" << endl;
            return true; // Dato encontrado
        }
        actual = actual->getSiguiente();
    }
    // cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
    return false; // Si no se encontró el dato, devolver false
}


template<typename T> 
 void Lista_Simple<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            if (anterior == NULL) {
                cabeza = aux->getSiguiente();
            }
            else {
                anterior->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        anterior = aux;
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T> 
 void Lista_Simple<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        cout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}

template<typename T>
Nodo<T>* Lista_Simple<T>::getCabeza() {
    return cabeza;
}