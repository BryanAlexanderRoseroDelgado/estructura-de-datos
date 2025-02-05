// nodo_ternario.h
#ifndef NODO_TERNARIO_H
#define NODO_TERNARIO_H

struct NodoTernario {
    char dato;
    bool esFinPalabra;
    NodoTernario *izquierdo, *central, *derecho;

    NodoTernario(char c) : dato(c), esFinPalabra(false), izquierdo(nullptr), central(nullptr), derecho(nullptr) {}
};

#endif // NODO_TERNARIO_H