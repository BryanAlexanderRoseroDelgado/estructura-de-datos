// arbol_ternario.cpp
#include "ArbolTernario.h"
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <graphics.h>

ArbolTernario::ArbolTernario() : raiz(nullptr) {}

ArbolTernario::~ArbolTernario() {
    destruirArbol(raiz);
}


void ArbolTernario::destruirArbol(NodoTernario* nodo) {
    if (!nodo) return;
    destruirArbol(nodo->izquierdo);
    destruirArbol(nodo->central);
    destruirArbol(nodo->derecho);
    delete nodo;
}

void ArbolTernario::insertar(const std::string& palabra) {
    if (!palabra.empty()) {
        raiz = insertarRecursivo(raiz, palabra, 0);
    }
}

NodoTernario* ArbolTernario::insertarRecursivo(NodoTernario* nodo, const std::string& palabra, int indice) {
    if (indice >= palabra.length()) return nodo;
    char letra = palabra[indice];

    if (!nodo) nodo = new NodoTernario(letra);

    if (letra < nodo->dato) {
        nodo->izquierdo = insertarRecursivo(nodo->izquierdo, palabra, indice);
    } else if (letra > nodo->dato) {
        nodo->derecho = insertarRecursivo(nodo->derecho, palabra, indice);
    } else {
        if (indice == palabra.length() - 1) {
            nodo->esFinPalabra = true;
        } else {
            nodo->central = insertarRecursivo(nodo->central, palabra, indice + 1);
        }
    }
    return nodo;
}

void ArbolTernario::imprimirRecursivo(NodoTernario* nodo, std::string palabra) {
    if (!nodo) return;
    imprimirRecursivo(nodo->izquierdo, palabra);
    palabra.push_back(nodo->dato);
    if (nodo->esFinPalabra) std::cout << palabra << "*" << std::endl;
    imprimirRecursivo(nodo->central, palabra);
    palabra.pop_back();
    imprimirRecursivo(nodo->derecho, palabra);
}

void ArbolTernario::imprimir() {
    imprimirRecursivo(raiz, "");
}

void ArbolTernario::graficar() {
    // Limpiar la pantalla antes de dibujar
    cleardevice();
    int x = getmaxx() / 2;
    int y = 50;
    setcolor(WHITE);
    graficarRecursivo(raiz, x, y, getmaxx() / 4);
}

void ArbolTernario::graficarRecursivo(NodoTernario* nodo, int x, int y, int distancia) {
    if (!nodo) return;

    // Dibujar el nodo
    circle(x, y, 20);
    char dato[2] = {nodo->dato, '\0'};
    outtextxy(x - 5, y - 5, dato);

    // Dibujar las líneas y los nodos hijos
    if (nodo->izquierdo) {
        line(x, y + 20, x - distancia, y + 50 - 20);
        graficarRecursivo(nodo->izquierdo, x - distancia, y + 50, distancia / 2);
    }
    if (nodo->central) {
        line(x, y + 20, x, y + 50 - 20);
        graficarRecursivo(nodo->central, x, y + 50, distancia / 2);
    }
    if (nodo->derecho) {
        line(x, y + 20, x + distancia, y + 50 - 20);
        graficarRecursivo(nodo->derecho, x + distancia, y + 50, distancia / 2);
    }
}

void ArbolTernario::recolectarNiveles(NodoTernario* nodo, int nivel, std::map<int, std::vector<std::string>>& niveles) {
    if (!nodo) return;
    std::string valor(1, nodo->dato);
    if (nodo->esFinPalabra) valor += "*";
    niveles[nivel].push_back(valor);
    recolectarNiveles(nodo->izquierdo, nivel + 1, niveles);
    recolectarNiveles(nodo->central, nivel + 1, niveles);
    recolectarNiveles(nodo->derecho, nivel + 1, niveles);
}

// Nueva función: calcular la altura del árbol
int ArbolTernario::altura(NodoTernario* nodo) {
    if (!nodo) return 0;
    int izq = altura(nodo->izquierdo);
    int der = altura(nodo->derecho);
    int central = altura(nodo->central);
    return std::max(std::max(izq, der), central) + 1;
}

int ArbolTernario::altura() {
    return altura(raiz);
}

// Nueva función: calcular la profundidad de un nodo
int ArbolTernario::profundidad(NodoTernario* nodo, char letra, int nivel) {
    if (!nodo) return -1;
    if (nodo->dato == letra) return nivel;
    int res = profundidad(nodo->izquierdo, letra, nivel + 1);
    if (res != -1) return res;
    res = profundidad(nodo->derecho, letra, nivel + 1);
    if (res != -1) return res;
    return profundidad(nodo->central, letra, nivel + 1);
}

int ArbolTernario::profundidad(char letra) {
    return profundidad(raiz, letra, 0);
}

// Recorrido preorden
void ArbolTernario::preorden(NodoTernario* nodo) {
    if (!nodo) return;
    std::cout << nodo->dato << " ";
    preorden(nodo->izquierdo);
    preorden(nodo->central);
    preorden(nodo->derecho);
}

void ArbolTernario::preorden() {
    preorden(raiz);
    std::cout << std::endl;
}

// Recorrido posorden
void ArbolTernario::posorden(NodoTernario* nodo) {
    if (!nodo) return;
    posorden(nodo->izquierdo);
    posorden(nodo->central);
    posorden(nodo->derecho);
    std::cout << nodo->dato << " ";
}

void ArbolTernario::posorden() {
    posorden(raiz);
    std::cout << std::endl;
}

// Recorrido en infijo
void ArbolTernario::infijo(NodoTernario* nodo) {
    if (!nodo) return;
    infijo(nodo->izquierdo);
    std::cout << nodo->dato << " ";
    infijo(nodo->central);
    infijo(nodo->derecho);
}

void ArbolTernario::infijo() {
    infijo(raiz);
    std::cout << std::endl;
}