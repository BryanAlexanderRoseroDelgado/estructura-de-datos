// arbol_ternario.h
#ifndef ARBOLTERNARIO_H
#define ARBOLTERNARIO_H

#include "NodoTernario.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

class ArbolTernario {
public:
    ArbolTernario();
    ~ArbolTernario();
    
    void insertar(const std::string& palabra);
    void imprimir();
    void graficar();
    
    int altura();  // Nueva función
    int profundidad(char letra);  // Nueva función
    
    void preorden();  // Nueva función
    void posorden();  // Nueva función
    void infijo();    // Nueva función

private:
    NodoTernario* raiz;
    
    NodoTernario* insertarRecursivo(NodoTernario* nodo, const std::string& palabra, int indice);
    void imprimirRecursivo(NodoTernario* nodo, std::string palabra);
    void graficarRecursivo(NodoTernario* nodo, int x, int y, int distancia);  // Nueva función
    void recolectarNiveles(NodoTernario* nodo, int nivel, std::map<int, std::vector<std::string>>& niveles);
    
    int altura(NodoTernario* nodo);  // Nueva función
    int profundidad(NodoTernario* nodo, char letra, int nivel);  // Nueva función
    
    void preorden(NodoTernario* nodo);  // Nueva función
    void posorden(NodoTernario* nodo);  // Nueva función
    void infijo(NodoTernario* nodo);    // Nueva función
    
    void destruirArbol(NodoTernario* nodo);
};

#endif // ARBOLTERNARIO_H
