/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Menu principal                                           *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "Menu.h"
#include "BackupManager.cpp"
#include <iostream>
#include "Validaciones.cpp" 
#include <conio.h> 
#include <vector>
#include <sstream>
#include <string>
#include <ctime>
#include "pdf_generator.h"
#include <windows.h>
#include "funciones.h"
#include "arbol_ternario.h"

using namespace std;

std::wstring getExecutablePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH); 
    std::wstring path(buffer);
    return path.substr(0, path.find_last_of(L"\\/"));
}
int ingresarAnio(const string& mensaje) {
    int anio;
    string input;
    while (true) {
        cout << mensaje;
        getline(cin, input);  // Usamos getline para permitir validación de la entrada completa

        // Validar si la entrada está vacía o contiene solo espacios
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            cout << "Error: Debe ingresar un dato (no puede estar vacío o contener solo espacios)." << endl;
            continue;
        }

        // Validar que el año sea numérico y tenga 4 dígitos
        try {
            anio = stoi(input);  // Convertimos la entrada a entero
            if (anio < 1 || anio > 2024) {
                throw invalid_argument("Año fuera de rango.");
            }
            break;  // Salimos del bucle si el año es válido
        } catch (const invalid_argument& e) {
            cout << "Error: Ingrese un año válido de 4 dígitos entre 0001 y 2024." << endl;
        }
    }
    return anio;
}
void mostrarMenu(ListaCircularDoble& lista) {
    ArbolTernario arbol;
    std::vector<std::string> titulos;
    std::vector<std::string> isbns;
    std::vector<std::string> isnis;
    std::vector<std::string> nombresAutores;
    std::vector<std::string> fechaNacs;
    std::vector<std::string> fechaPubs;

    ListaCircularMenu menuOpciones;
    menuOpciones.insertar("Agregar libro");
    menuOpciones.insertar("Buscar libro");
    menuOpciones.insertar("Eliminar libro");
    menuOpciones.insertar("Ver todos los libros");
    menuOpciones.insertar("Exportar en archivo PDF");
    menuOpciones.insertar("Crear backup");
    menuOpciones.insertar("Restaurar backup");
    menuOpciones.insertar("Buscar por rango");
    menuOpciones.insertar("Obtener elementos de prefijo comun");
    menuOpciones.insertar("Salir");

    int seleccion = 0;
    string ruta = "libros.txt";
    int anioInicio, anioFin;

    while (true) {
        system("cls");
        cout << "=== Menu Principal ===\n";
        NodoMenu* actual = menuOpciones.getPrimero();
        for (int i = 0; i < menuOpciones.getTamano(); i++) {
            if (i == seleccion)
                cout << ">> " << actual->dato << " <<\n";
            else
                cout << "   " << actual->dato << endl;
            actual = actual->siguiente;
        }

        char tecla = _getch();
        if (tecla == 72) { // Flecha Arriba
            seleccion = (seleccion - 1 + menuOpciones.getTamano()) % menuOpciones.getTamano();
        } else if (tecla == 80) { // Flecha Abajo
            seleccion = (seleccion + 1) % menuOpciones.getTamano();
        } else if (tecla == '\r') { // Enter
            string opcionSeleccionada = menuOpciones.obtenerOpcion(seleccion);

            if (opcionSeleccionada == "Agregar libro") {
                string titulo, isbn, isni;
                string fechaPub, fechaNac;
                Persona autor;
                do {
                    cout << "Ingrese título del libro (o presione Enter para regresar al menú): ";
                    titulos = {};
                    titulos=lista.generarArreglo("titulo");

                    // Usamos la función de autocompletado
                    titulo = arbol.autocompletar(titulos);
                    
                    if (titulo.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break; // Regresa al menú principal
                    }
                } while (!Validaciones::validarTitulo(titulo, "Título"));

                if (titulo.empty()) continue; // Regresa al menú principal si el título está vacío

                do {
                    cout << "Ingrese ISBN (o presione Enter para regresar al menú): ";
                    
                    // Generamos el arreglo de ISBNs almacenados en la lista circular
                    isbns = {};
                    isbns = lista.generarArreglo("isbn");

                    // Usamos la función de autocompletado
                    isbn = arbol.autocompletar(isbns);

                    if (isbn.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break; // Regresa al menú principal
                    }
                } while (!Validaciones::validarIsbn(isbn));

                if (isbn.empty()) continue;  // Regresa al menú principal si el ISBN está vacío

                Nodo* libroExistente = lista.buscarLibroPorIsbn(isbn);
                if (libroExistente) {
                    cout << "El ISBN ya existe. Información del libro existente:\n";
                    libroExistente->libro.mostrar();
                } else {
                    do {
                        cout << "Ingrese ISNI del autor (o presione Enter para regresar al menú): ";
                        isnis= {};
                        isnis=lista.generarArreglo("isni");
                        
                        // Usamos la función de autocompletado
                        isni = arbol.autocompletar(isnis);

                        if (isni.empty()) {
                            cout << "Regresando al menú principal...\n";
                            break; // Regresa al menú principal
                        }
                    } while (!Validaciones::validarIsni(isni));

                    if (isni.empty()) continue; // Regresa al menú principal si el ISNI está vacío

                    Persona autorExistente = lista.buscarAutorPorIsni(isni);
                    if (autorExistente.getNombre() != "") {
                        cout << "Autor existente encontrado. Usando información del autor.\n";
                        autor = autorExistente;
                        // Guardamos la fecha de nacimiento del autor existente
                        fechaNac = autorExistente.getFechaNacimiento().toString();
                    } else {
                        string nombreAutor;
                        do {
                            cout << "Ingrese nombre del autor (o presione Enter para regresar al menú): ";
                            nombresAutores= {};
                            nombresAutores=lista.generarArreglo("nombreAutor");

                            // Usamos la función de autocompletado
                            nombreAutor = arbol.autocompletar(nombresAutores);
                            
                            if (nombreAutor.empty()) {
                                cout << "Regresando al menú principal...\n";
                                break; // Regresa al menú principal
                            }
                        } while (!Validaciones::validarTituloNombre(nombreAutor, "Nombre del Autor"));

                        if (nombreAutor.empty()) continue; // Regresa al menú principal si el nombre del autor está vacío

                        do {
                            cout << "Ingrese fecha de nacimiento del autor (DD-MM-YYYY) (o presione Enter para regresar al menú): ";
                            fechaNacs= {};
                            fechaNacs=lista.generarArreglo("fechaNac");

                            // Usamos la función de autocompletado
                            fechaNac = arbol.autocompletar(fechaNacs);
                            
                            if (fechaNac.empty()) {
                                cout << "Regresando al menú principal...\n";
                                break; // Regresa al menú principal
                            }
                        } while (!Validaciones::validarFecha(fechaNac));

                        if (fechaNac.empty()) continue; // Regresa al menú principal si la fecha de nacimiento está vacía

                        Fecha fechaNacimientoAutor = Fecha::crearDesdeCadena(fechaNac);
                        autor = Persona(nombreAutor, isni, fechaNacimientoAutor);
                    }

                    do {
                        cout << "Ingrese fecha de publicación del libro (DD-MM-YYYY) (o presione Enter para regresar al menú): ";
                        fechaPubs= {};
                        fechaPubs=lista.generarArreglo("fechaPub");

                        // Usamos la función de autocompletado
                        fechaPub = arbol.autocompletar(fechaPubs);
                        
                        if (fechaPub.empty()) {
                            cout << "Regresando al menú principal...\n";
                            break; // Regresa al menú principal
                        }
                    } while (!Validaciones::validarFechaPublicacion(fechaPub, fechaNac));

                    if (fechaPub.empty()) continue; // Regresa al menú principal si la fecha de publicación está vacía

                    Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
                    Libro libro(titulo, isbn, autor, fechaPublicacion);
                    lista.agregarLibro(libro);
                }
            } else if (opcionSeleccionada == "Buscar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a buscar (presione Enter para volver al menú principal): ";
                isbns={};
                isbns=lista.generarArreglo("isbn");
                
                // Usamos la función de autocompletado
                isbn = arbol.autocompletar(isbns);
                
                if (isbn.empty()) {
                    cout << "Regresando al menú principal...\n";
                    system("cls"); // Limpia la consola antes de regresar
                    continue;      // Regresa al menú principal
                }
                Nodo* libro = lista.buscarLibroPorIsbn(isbn);
                if (libro) {
                    libro->libro.mostrar();
                } else {
                    cout << "Libro no encontrado.\n";
                }
            } else if (opcionSeleccionada == "Eliminar libro") {
                string isbn;
                cout << "Ingrese el ISBN del libro a eliminar (presione Enter para volver al menú principal): ";
                isbns={};
                isbns=lista.generarArreglo("isbn");

                // Usamos la función de autocompletado
                isbn = arbol.autocompletar(isbns);
                
                if (isbn.empty()) {
                    cout << "Regresando al menú principal...\n";
                    system("cls"); // Limpia la consola antes de regresar
                    continue;      // Regresa al menú principal
                }
                Nodo* libroAEliminar = lista.buscarLibroPorIsbn(isbn);
                if (libroAEliminar) {
                    string titulo = libroAEliminar->libro.getTitulo();
                    lista.eliminarLibro(titulo);
                    cout << "Libro eliminado exitosamente.\n";
                } else {
                    cout << "Libro no encontrado con ISBN: " << isbn << endl;
                }
            }else if (opcionSeleccionada == "Ver todos los libros") {
                lista.imprimirLibros();
            } else if (opcionSeleccionada == "Exportar en archivo PDF") {
                const std::string inputFile = "libros.txt";
                createPDF(inputFile);
            } else if (opcionSeleccionada == "Crear backup") {
                time_t ahora = time(0);
                tm* tiempo = localtime(&ahora);
                stringstream ss;
                ss << (1900 + tiempo->tm_year) << "_" << (1 + tiempo->tm_mon) << "_" << tiempo->tm_mday << "_"
                << tiempo->tm_hour << "_" << tiempo->tm_min << "_" << tiempo->tm_sec << ".txt";
                lista.crearBackup(ss.str());
            } else if (opcionSeleccionada == "Restaurar backup") {
                BackupManager::restaurarBackup(lista);
            } else if (opcionSeleccionada == "Buscar por rango") {
                while (true) {
                    string inputAnioInicio, inputAnioFin;

                    // Solicitar el año de fin
                    cout << "Ingrese el año de fin (0001 a 2025) (o presione Enter para regresar al menú): ";
                    getline(cin, inputAnioFin);
                    if (inputAnioFin.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break; // Regresa al menú principal si el campo está vacío
                    }

                    // Solicitar el año de inicio
                    cout << "Ingrese el año de inicio (0001 a 2025) (o presione Enter para regresar al menú): ";
                    getline(cin, inputAnioInicio);
                    if (inputAnioInicio.empty()) {
                        cout << "Regresando al menú principal...\n";
                        break; // Regresa al menú principal si el campo está vacío
                    }

                    try {
                        // Convertir entradas a enteros
                        anioFin = stoi(inputAnioFin);
                        anioInicio = stoi(inputAnioInicio);

                        // Validar si los años están dentro del rango permitido
                        if (anioInicio < 1 || anioInicio > 2025 || anioFin < 1 || anioFin > 2025) {
                            cout << "Error: Los años deben estar en el rango de 0001 a 2025.\n";
                            continue; // Vuelve a solicitar los años
                        }

                        // Validar el rango de los años
                        if (anioFin > anioInicio) {
                            cout << "Registros encontrados entre " << anioInicio << " y " << anioFin << ":\n";
                            buscarPorRango(ruta, anioInicio, anioFin); // Realizar la búsqueda
                            break; // Salir del bucle si la búsqueda fue exitosa
                        } else {
                            cout << "Error: El año de fin debe ser mayor al año de inicio, y no pueden ser iguales.\n";
                        }
                    } catch (const invalid_argument&) {
                        cout << "Error: Entrada inválida. Por favor, ingrese un año válido.\n";
                    } catch (const out_of_range&) {
                        cout << "Error: El año ingresado está fuera del rango permitido.\n";
                    }
            }
        } else if (opcionSeleccionada == "Obtener elementos de prefijo comun") {
            string termino;
            string clave="";
            cout<<"Escoja el tipo de dato que quiere analizar de los libros"<<endl;
            cout<<"1. Titulo"<<endl;
            cout<<"2. ISBN"<<endl;
            cout<<"3. ISNI"<<endl;
            cout<<"4. Nombre del autor"<<endl;
            cout<<"5. Fecha de nacimiento del autor"<<endl;
            cout<<"6. Fecha de publicacion"<<endl;
            cout<<"Ingrese el numero de la opcion que desea: ";
            int opcion; 
            cin>>opcion;
            while (opcion<1 || opcion>6){
                cout<<"Ingrese una opcion valida"<<endl;
                cin>>opcion;
            }
            cin.ignore();

            if(opcion==1){
                clave="titulo";
            }else if(opcion==2){
                clave="isbn";
            }else if(opcion==3){
                clave="isni";
            }else if(opcion==4){
                clave="nombreAutor";
            }else if(opcion==5){
                clave="fechaNac";
            }else if(opcion==6){
                clave="fechaPub";
            }

            cout << "Ingrese el prefijo a buscar (o presione Enter para volver al menú principal): ";
            getline(cin,termino);
            if (termino.empty()) {
                cout << "Regresando al menú principal...\n";
                continue; // Regresa al menú principal
            }

            arbol.elemento_comun(termino,clave);

        }else if (opcionSeleccionada == "Salir") {
                break;
            }
            cout << "Presione cualquier tecla para continuar...\n";
            _getch();
        } else if (tecla == 59) { // F1
            std::wstring base_path = getExecutablePath();
            std::wstring ayuda_path = base_path + L"\\output\\ayuda.exe";
            std::string command = "start cmd /C \"" + std::string(ayuda_path.begin(), ayuda_path.end()) + "\"";
            system(command.c_str());
        }
    }
}