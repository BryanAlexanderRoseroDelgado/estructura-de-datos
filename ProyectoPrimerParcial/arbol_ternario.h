// arbol_ternario.h
#ifndef ARBOL_TERNARIO_H
#define ARBOL_TERNARIO_H

#include "nodo_ternario.h"
#include <vector>
#include <string>
#include <iostream>

class ArbolTernario {
public:
    NodoTernario* raiz;

    ArbolTernario();
    ~ArbolTernario();
    void crearArbol(const std::vector<std::string>& palabras);
    std::string autocompletar(const std::vector<std::string>& palabras);
    void elemento_comun(const std::string& termino, const std::string& clave);
    void destruirArbol(NodoTernario* nodo);
private:
    NodoTernario* insertar(NodoTernario* nodo, const std::string& palabra, int index);
    void buscarSugerencia(NodoTernario* nodo, std::string prefijo, std::string& sugerencia);
    void obtenerElementosComunes(NodoTernario* nodo, std::string prefijo, std::vector<std::string>& resultados);
};

#endif // ARBOL_TERNARIO_H