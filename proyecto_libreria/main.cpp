/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//main.cpp
#include "ListaCircularDoble.cpp"
#include <iostream>
#include <string>
#include "Libro.cpp"
#include "Autor.cpp"
#include <ctime> 

using namespace std;

int main() {
    ListaCircularDoble <Libro> lista_Libros;
    ListaCircularDoble <Autor> lista_autores;
    ListaCircularDoble <Libro> lista_BackUp; 
    
    int opcion;
    Validaciones validaciones;

    //cargar lista_libros y lista_autores desde el txt
    lista_Libros.cargarDesdeArchivo("libros.txt");
    lista_autores.cargarDesdeArchivo("autores.txt");

    do {
        cout << "*********** INFORMACION LIBROS ***********" << endl;
        cout << "1. Insertar Libro" << endl;
        cout << "2. Buscar Libro" << endl;
        cout << "3. Eliminar Libro" << endl;
        cout << "4. Mostrar Libro" << endl;
        cout << "5. Buscar Autor" << endl;
        cout << "6. Borrar Autor" << endl;
        cout << "7. Mostrar autores" << endl;
        cout << "8. Crear respaldo del registro actual de libros"<< endl;
        cout << "9. Cargar respaldo desde la carpeta"<< endl;
        cout << "10. Hacer busqueda de libros por fechas"<< endl;
        cout << "11. Salir" << endl;
        cout << "Escoja una opción: ";
        cin>>opcion;

        /*vector<string> opciones = {
        "Insertar Libro", "Buscar Libro", "Eliminar Libro", "Mostrar Libro", 
        "Buscar Autor", "Borrar Autor", "Mostrar Autores", 
        "Crear respaldo del registro actual de libros", "Cargar respaldo desde la carpeta", "Salir"
        };
        
        opcion=validar.mostrarMenuConCursor(opciones);*/

        switch (opcion) {
        case 1: {
            lista_Libros.guardarEnArchivo("backup.txt");//guardado el estado previo de la lista
            Libro libro;
            std::string ISNB,nombreLibro,nombre,apellido;
            std::time_t tiempo = std::time(nullptr); // Obtener el tiempo actual como un valor de tipo time_t
            std::tm* fecha_local = std::localtime(&tiempo);

            cout << "Ingrese el ISNB: " << endl;
            ISNB=validaciones.validarISBN();
            lista_Libros.verificar_INSB(ISNB);
            libro.set_ISNB(ISNB);
 
            cout << "Ingrese el nombre del libro: " << endl;
            std::cin.ignore();
            std::getline(std::cin,nombreLibro);//sin validacion
            libro.set_nombre_libro(nombreLibro);

            cout << "Ingrese el nombre del autor: " << endl;
            nombre=validaciones.ingresar_string();
            libro.set_nombre_autor(nombre);

            cout << "Ingrese el apellido del autor: " << endl;
            apellido=validaciones.ingresar_string();
            libro.set_apellido_autor(apellido);

            libro.set_fecha_registro(*fecha_local);

            lista_autores.validar_autor(nombre,apellido,lista_autores);//validar que el autor ingresado exista
            ///errores en la fecha del autor(el programa se detiene al ingresar mal el dato) no se guarda de forma correcta en el txt
            lista_Libros.insertar(libro);

            lista_Libros.guardarEnArchivo("libros.txt");
            lista_autores.guardarEnArchivo("autores.txt");
            break;
        }
        case 2: {
            int op;
            std::string criterioA="",criterioB="";

            cout << "**** Seleccione criterio de búsqueda ****" << endl;
            cout << "1. ISNB" << endl;
            cout << "2. Nombre del libro" << endl;
            cout << "3. Autor" << endl;
            cout << "Ingrese una opción: ";
            op = validaciones.ingresar_entero('3');

            if (op == 1) {
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterioA = validaciones.validarISBN();
            } else if (op == 2) {
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                std::getline(std::cin,criterioA);//sin validacion
            } else if (op == 3) {
                cout << "****Escriba el dato exacto de busqueda (nombre)*****" << endl;
                criterioA = validaciones.ingresar_string();
                cout << "****Escriba el dato exacto de busqueda (apellido)*****" << endl;
                criterioB = validaciones.ingresar_string();
            }

            lista_Libros.buscar(op, criterioA, criterioB);
            break;
        }    
        case 3: {
            lista_Libros.guardarEnArchivo("backup.txt");//guardado el estado previo de la lista

            int op1;
            std::string criterioC="",criterioD="";

            cout << "**** Seleccione criterio de búsqueda para la eliminacion****" << endl;
            cout << "1. ISNB" << endl;
            cout << "2. Nombre del libro" << endl;
            cout << "3. Autor" << endl;
            cout << "Ingrese una opción: ";
            op1 = validaciones.ingresar_entero('3');

            if (op1 == 1) {
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                criterioC = validaciones.validarISBN();
            } else if (op1 == 2) {
                cout << "****Escriba el dato exacto de busqueda*****" << endl;
                std::getline(std::cin,criterioC);//sin validacion//sin validacion
            } else if (op1 == 3) {
                cout << "****Escriba el dato exacto de busqueda (nombre)*****" << endl;
                criterioC = validaciones.ingresar_string();
                cout << "****Escriba el dato exacto de busqueda (apellido)*****" << endl;
                criterioD = validaciones.ingresar_string();
            }
            
            lista_Libros.eliminar(op1, criterioC, criterioD);//solo elimina un elemento sin importar si hay coincidencias(corregir)
            lista_Libros.guardarEnArchivo("libros.txt");
            break;
        }
        case 4:{
            cout << "**Lista libros**" << endl;
            lista_Libros.mostrar();
            break;
        }
        case 5:{
            //buscar autor(parametro nombre y apellido)
            std::string nombre_autor, apellido_autor;
            cout << "Ingrese el nombre del autor a buscar: " << endl;
            nombre_autor=validaciones.ingresar_string();

            cout << "Ingrese el apellido del autor a buscar: " << endl;
            apellido_autor=validaciones.ingresar_string();

            lista_autores.buscar_autor(nombre_autor,apellido_autor);
            break;
        }
        case 6:{
            //borrar autor((parametro nombre y apellido))
            std::string nombre_autor, apellido_autor;
            cout << "Ingrese el nombre del autor a eliminar: " << endl;
            nombre_autor=validaciones.ingresar_string();

            cout << "Ingrese el apellido del autor a eliminar: " << endl;
            apellido_autor=validaciones.ingresar_string();

            lista_autores.eliminar_autor(nombre_autor,apellido_autor);
            break;
        } 
        case 7:{
            cout << "**Lista autoreS**" << endl;
            lista_autores.mostrar_autor();
            break;
        }
        case 8:{
            cout << "Creando respaldo del registro actual de libros..." << endl;
            lista_Libros.guardarRespaldo();
            break;
        }    
        case 9: {
            char respuesta;
            std::cout << "¿Desea crear un respaldo de la lista actual antes de cargar un respaldo? (s/n): ";
            respuesta=validar.leerLetra();

            if (respuesta == 's' || respuesta == 'S') {
                lista_Libros.guardarRespaldo();
                std::cout << "Respaldo creado exitosamente.\n";
            }

            // Mostrar el menú de archivos de respaldo
            lista_Libros.restaurarRespaldo();
            break;
        }
        case 10:{
            std::string anio1,anio2;
            cout << "Ingrese la fecha de inicio: " << endl;
            anio1=validaciones.ingresar_ISNB(4);

            cout << "Ingrese la fecha final: " << endl;
            anio2=validaciones.ingresar_ISNB(4);

            int year1 = std::stoi(anio1);
            int year2 = std::stoi(anio2);

            while (year1 >= year2) {
                std::cout << "Error: El primer año debe ser menor que el segundo. Intente de nuevo.\n";

                cout << "Ingrese el nombre del autor a eliminar: " << endl;
                anio1=validaciones.ingresar_ISNB(4);

                cout << "Ingrese el apellido del autor a eliminar: " << endl;
                anio2=validaciones.ingresar_ISNB(4);

                int year1 = std::stoi(anio1);
                int year2 = std::stoi(anio2);
            }
            lista_Libros.buscar_por_fecha(year1,year2);


        }
        case 11:{
            cout << "Saliendo del programa..." << endl;
            break;
        }
        default:{
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
        }
    }while (opcion != 11);
        return 0;
} 

