#include "funciones.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip> // Para std::setw y std::left
#include <algorithm> // Para std::sort

using namespace std;

// Función para dividir una línea por un delimitador
vector<string> dividir(const std::string& linea, char delimitador) {
    vector<string> partes;
    stringstream ss(linea);
    string parte;
    while (getline(ss, parte, delimitador)) {
        partes.push_back(parte);
    }
    return partes;
}

// Función para imprimir la cabecera formateada
void imprimirCabecera() {
    cout << left;
    cout << setw(40) << "Título"
         << setw(25) << "Autor"
         << setw(22) << "ISNI"
         << setw(20) << "ISBN"
         << setw(15) << "Publicación"
         << "Nac. Autor" << endl;

    cout << string(120, '-') << endl; // Línea divisoria
    cout << "\n";
}

// Function to perform binary search on a sorted vector of records
vector<vector<string>> buscarPorRangoBinario(const vector<vector<string>>& registros, int anioInicio, int anioFin) {
    vector<vector<string>> resultados;
    int izquierda = 0;
    int derecha = registros.size() - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        int anioMedio = stoi(registros[medio][5].substr(registros[medio][5].size() - 4));

        if (anioMedio >= anioInicio && anioMedio <= anioFin) {
            // Encontrar el rango completo de registros dentro del rango
            int i = medio;
            while (i >= 0 && stoi(registros[i][5].substr(registros[i][5].size() - 4)) >= anioInicio) {
                if (stoi(registros[i][5].substr(registros[i][5].size() - 4)) <= anioFin) {
                    resultados.push_back(registros[i]);
                }
                i--;
            }
            i = medio + 1;
            while (i < registros.size() && stoi(registros[i][5].substr(registros[i][5].size() - 4)) <= anioFin) {
                if (stoi(registros[i][5].substr(registros[i][5].size() - 4)) >= anioInicio) {
                    resultados.push_back(registros[i]);
                }
                i++;
            }
            break;
        } else if (anioMedio < anioInicio) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return resultados;
}

// Función para buscar registros en un rango de años usando búsqueda binaria
void buscarPorRango(const std::string& rutaArchivo, int anioInicio, int anioFin) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    vector<vector<string>> registros;
    string linea;
    while (getline(archivo, linea)) {
        vector<string> campos = dividir(linea, ';');
        if (campos.size() >= 6) {
            registros.push_back(campos);
        }
    }
    archivo.close();

    // Ordenar registros por año de publicación
    sort(registros.begin(), registros.end(), [](const vector<string>& a, const vector<string>& b) {
        return stoi(a[5].substr(a[5].size() - 4)) < stoi(b[5].substr(b[5].size() - 4));
    });

    // Realizar búsqueda binaria en los registros ordenados
    vector<vector<string>> resultados = buscarPorRangoBinario(registros, anioInicio, anioFin);

    if (!resultados.empty()) {
        imprimirCabecera();
        for (const auto& registro : resultados) {
            cout << left;
            cout << setw(40) << registro[0]
                 << setw(25) << registro[1]
                 << setw(22) << registro[2]
                 << setw(20) << registro[4]
                 << setw(15) << registro[5]
                 << registro[3] << endl;
        }
    } else {
        cout << "No se encontraron registros en el rango de años especificado." << endl;
    }
}
