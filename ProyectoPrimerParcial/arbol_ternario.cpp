// arbol_ternario.cpp
#include "arbol_ternario.h"

ArbolTernario::ArbolTernario() : raiz(nullptr) {}

ArbolTernario::~ArbolTernario() {
    destruirArbol(raiz);
}

void ArbolTernario::destruirArbol(NodoTernario* nodo) {
    if (nodo) {
        destruirArbol(nodo->izquierdo);
        destruirArbol(nodo->central);
        destruirArbol(nodo->derecho);
        delete nodo;
    }
}

NodoTernario* ArbolTernario::insertar(NodoTernario* nodo, const std::string& palabra, int index) {
    if (index >= palabra.size()) return nodo;
    
    char caracter = palabra[index];
    if (!nodo) nodo = new NodoTernario(caracter);
    
    if (caracter < nodo->dato) {
        nodo->izquierdo = insertar(nodo->izquierdo, palabra, index);
    } else if (caracter > nodo->dato) {
        nodo->derecho = insertar(nodo->derecho, palabra, index);
    } else {
        if (index == palabra.size() - 1) {
            nodo->esFinDePalabra = true;
        } else {
            nodo->central = insertar(nodo->central, palabra, index + 1);
        }
    }
    return nodo;
}

void ArbolTernario::crearArbol(const std::vector<std::string>& palabras) {
    for (const std::string& palabra : palabras) {
        raiz = insertar(raiz, palabra, 0);
    }
}

void ArbolTernario::buscarSugerencia(NodoTernario* nodo, std::string prefijo, std::string& sugerencia) {
    if (!nodo) return;
    
    if (nodo->esFinDePalabra) {
        sugerencia = prefijo;
        return;
    }
    
    if (nodo->central) {
        buscarSugerencia(nodo->central, prefijo + nodo->dato, sugerencia);
    }
}

std::string ArbolTernario::autocompletar(const std::vector<std::string>& palabras) {
    crearArbol(palabras);
    std::string entrada = "", sugerencia = "";
    char c;
  
    while (true) {
        c = std::cin.get();
        if (c == '\n') break;
        
        entrada += c;
        sugerencia = "";
        NodoTernario* nodo = raiz;
        int i = 0;
        
        while (nodo && i < entrada.size()) {
            if (entrada[i] < nodo->dato) {
                nodo = nodo->izquierdo;
            } else if (entrada[i] > nodo->dato) {
                nodo = nodo->derecho;
            } else {
                if (i == entrada.size() - 1) {
                    buscarSugerencia(nodo->central, entrada, sugerencia);
                }
                nodo = nodo->central;
                i++;
            }
        }
        
        if (!sugerencia.empty()) {
            std::cout << "\r" << entrada << sugerencia.substr(entrada.size()) << std::flush;
        }
    }
    return entrada;
}

void ArbolTernario::obtenerElementosComunes(NodoTernario* nodo, std::string prefijo, std::vector<std::string>& resultados) {
    if (!nodo) return;
    
    if (nodo->esFinDePalabra) {
        resultados.push_back(prefijo);
    }
    
    obtenerElementosComunes(nodo->izquierdo, prefijo, resultados);
    obtenerElementosComunes(nodo->central, prefijo + nodo->dato, resultados);
    obtenerElementosComunes(nodo->derecho, prefijo, resultados);
}

void ArbolTernario::elemento_comun(const std::string& termino, const std::string& clave) {
    std::vector<std::string> palabras = {/* Aquí se generaría el arreglo con clave */};
    crearArbol(palabras);
    NodoTernario* nodo = raiz;
    
    for (char c : termino) {
        while (nodo && nodo->dato != c) {
            if (c < nodo->dato) nodo = nodo->izquierdo;
            else nodo = nodo->derecho;
        }
        if (!nodo) return;
        nodo = nodo->central;
    }
    
    std::vector<std::string> resultados;
    obtenerElementosComunes(nodo, termino, resultados);
    
    std::cout << "Elementos en común con '" << termino << "':\n";
    for (const std::string& palabra : resultados) {
        std::cout << "- " << palabra << "\n";
    }
}
