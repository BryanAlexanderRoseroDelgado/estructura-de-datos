// nodo_ternario.h
#ifndef NODO_TERNARIO_H
#define NODO_TERNARIO_H

class NodoTernario {
public:
    char dato;
    bool esFinDePalabra;
    NodoTernario* izquierdo;
    NodoTernario* central;
    NodoTernario* derecho;

    NodoTernario(char valor);
};

#endif // NODO_TERNARIO_H

