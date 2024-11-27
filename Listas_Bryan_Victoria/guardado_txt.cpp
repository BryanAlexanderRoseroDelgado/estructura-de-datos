#include "guardado_txt.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

void guardado_txt::guardar(const std::string &nombreArchivo, Lista_Simple<Persona> &listaPersonas){
    //std::ofstream archivo(nombreArchivo, std::ios::out); // Abrir archivo en modo sobre escritura
    std::ofstream archivo(nombreArchivo, std::ios::app); // Abrir archivo en modo adición

        if (!archivo) {
            std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
            return;
        }

    Nodo<Persona>* actual = listaPersonas.getCabeza(); // Obtener la cabeza de la lista

        while (actual != nullptr) {
            archivo << actual->getDato(); // Usamos el operador << sobrecargado de Persona
            archivo << " -> NULL\n";     //simular el fin de la lista// puede ser util para guardar una lista modificada, caso contrario borrar linea
            actual = actual->getSiguiente();
        }

    archivo.close();
}

void guardado_txt::buscarPorCriterio(const std::string& nombreArchivo, const std::string& criterio){
    std::ifstream archivo(nombreArchivo); // Abrir el archivo en modo lectura

    if (!archivo) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    Lista_Simple<std::string> listaTemporal; // Lista para almacenar cada conjunto de datos
    bool encontrado = false;

    std::cout << "Buscando listas que coincidan con el criterio: \"" << criterio << "\"\n";

    while (std::getline(archivo, linea)) { // Leer línea por línea
        if (linea.find("-> NULL") == std::string::npos) {
            // Si no es el final de la lista, añadir la línea actual como un dato a la lista temporal
            listaTemporal.Insertar_cola(linea);
        } else {
            // Si encontramos "-> NULL", evaluamos la lista temporal
            if (listaTemporal.Buscar(criterio)) {
                // Si el criterio está presente, mostramos toda la lista
                Nodo<std::string>* actual = listaTemporal.getCabeza();
                while (actual != nullptr) {
                    std::cout << actual->getDato() << "\n";
                    actual = actual->getSiguiente();
                }
                std::cout << " -> NULL\n"; // Simular el final de la lista en el archivo
                encontrado = true;
            }
            // Reiniciar la lista temporal para procesar la siguiente lista
            listaTemporal = Lista_Simple<std::string>();
        }
    }

    archivo.close();

    if (!encontrado) {
        std::cout << "No se encontraron listas que coincidan con el criterio: \"" << criterio << "\".\n";
    }
}

void guardado_txt::EliminarPorCriterioEnArchivo(const std::string& nombreArchivo, const std::string& criterio, const std::string& valor) {
        std::ifstream archivoEntrada(nombreArchivo);
        if (!archivoEntrada.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
            return;
        }

        std::vector<std::string> listasFiltradas;
        std::string linea;
        std::ostringstream listaActual;
        bool coincide = false;

        // Leer y procesar el archivo línea por línea
        while (std::getline(archivoEntrada, linea)) {
            if (linea.find("-> NULL") != std::string::npos) {
                // Si es el final de una lista, verificar coincidencia
                listaActual << linea << "\n";
                if (!coincide) {
                    listasFiltradas.push_back(listaActual.str());
                }
                listaActual.str("");
                listaActual.clear();
                coincide = false; // Resetear la coincidencia para la siguiente lista
            } else {
                listaActual << linea << "\n";
                if (linea.find(criterio + valor) != std::string::npos) {
                    coincide = true; // Marcar la lista como coincidente si se encuentra el criterio + valor
                }
            }
        }

        archivoEntrada.close();

        // Escribir las listas no coincidentes de vuelta al archivo
        std::ofstream archivoSalida(nombreArchivo, std::ios::trunc);
        if (!archivoSalida.is_open()) {
            std::cerr << "No se pudo abrir el archivo para escritura: " << nombreArchivo << std::endl;
            return;
        }

        for (const auto& lista : listasFiltradas) {
            archivoSalida << lista;
        }

        archivoSalida.close();

        std::cout << "Listas que coinciden con el criterio \"" << criterio << valor << "\" han sido eliminadas.\n";
}

void guardado_txt::MostrarListasDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Abrir el archivo en modo lectura

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << "." << std::endl;
        return;
    }

    std::string linea;
    std::cout << "**** Listas existentes en el archivo ****" << std::endl;

    while (std::getline(archivo, linea)) { // Leer línea por línea
        std::cout << linea << std::endl;  // Mostrar la línea en la terminal
    }

    archivo.close(); // Cerrar el archivo
}

