/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Cameron Victoria Diaz Caisaluisa
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//Main.cpp
#include "Lista_Simple.cpp"
#include "Nodo.h"
#include "ValidarPersona.cpp"
#include "guardado_txt.cpp"
#include <iostream>
#include <limits> // Para std::numeric_limits
#include <string>

using namespace std;

int main() {
    Lista_Simple<Persona> lista_Persona;
    int opcion;

    ValidarPersona ingresar_string;
    guardado_txt almacenamiento_txt;

    do {
        cout << "***********Listas Simples***********" << endl;
        cout << "1. Insertar Lista" << endl;
        cout << "2. Buscar Lista" << endl;
        cout << "3. Eliminar listas" << endl;
        cout << "4. Mostrar Lista" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opcion: " << endl;
        opcion=ingresar_string.ingresar_del_1_al_5();


        switch (opcion) {
        case 1: {
            char continuar;
            do {
                Persona sujeto;
                ingresar_string.ingresar_cedula("Ingrese la cédula: ", sujeto);
                ingresar_string.ingresar_nombre("Ingrese el nombre: ", sujeto);
                ingresar_string.ingresar_apellido("Ingrese el apellido: ", sujeto);

                lista_Persona.Insertar_cola(sujeto);
                almacenamiento_txt.guardar("personas_lista.txt", lista_Persona);

                cout << "¿Desea agregar otra persona? (s/n): ";
                cin >> continuar;
                cin.ignore();
            } while (tolower(continuar) == 's');
            break;
        }
        case 2: {
            int op;
            std::string opcion;
            std::string criterio;
            std::string resultado;

            cout << "**** Seleccione criterio de búsqueda ****" << endl;
            cout << "1. Cédula" << endl;
            cout << "2. Nombre" << endl;
            cout << "3. Apellido" << endl;
            cout << "Ingrese una opción: ";
            op=ingresar_string.ingresar_del_1_al_3();

            if (op == 1) {
                opcion = "Cédula: ";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                cin.ignore(); // Limpiar el buffer de entrada
                criterio=ingresar_string.ingresar_cedula_sin_persona();

            } else if (op == 2) {
                opcion = "Nombre: ";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                cin.ignore(); // Limpiar el buffer de entrada
                criterio=ingresar_string.ingresar_nombre_sin_persona();

            } else if (op == 3) {
                opcion = "Apellido: ";
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                cin.ignore(); // Limpiar el buffer de entrada
                criterio=ingresar_string.ingresar_apellido_sin_persona();

            }

            resultado=opcion+criterio;

            almacenamiento_txt.buscarPorCriterio("personas_lista.txt", resultado);

            break;
        }
        case 3: {
            int op1;
            std::string opcion1;
            std::string criterio1;

            cout << "**** Seleccione criterio de búsqueda ****" << endl;
            cout << "1. Cédula" << endl;
            cout << "2. Nombre" << endl;
            cout << "3. Apellido" << endl;
            cout << "Ingrese una opción: ";
            op1=ingresar_string.ingresar_del_1_al_3();

            if (op1 == 1) {
                opcion1 = "Cédula: ";
            } else if (op1 == 2) {
                opcion1 = "Nombre: ";
            } else if (op1 == 3) {
                opcion1 = "Apellido: ";
            }
            cout << "****Ingrese el termino en comun que tendran las listas para su eliminacion ****" << endl;
            cin.ignore(); // Limpiar el buffer antes de usar getline
            std::getline(cin, criterio1);

            almacenamiento_txt.EliminarPorCriterioEnArchivo("personas_lista.txt", opcion1,criterio1);

            break;
        }
        case 4: {
            almacenamiento_txt.MostrarListasDesdeArchivo("personas_lista.txt");
            break;
        }
        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        }
    } while (opcion != 5);

    return 0;
}
