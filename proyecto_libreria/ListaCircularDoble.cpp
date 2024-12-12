/*************************
 * UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE
 * ALUMNO:  Bryan Alexander Rosero Delgado, Victoria Diaz
 * FECHA CREACION: Jueves,  21 de noviembre de 2024
 * FECHA MODIFICACION: Jueves,  21 de noviembre de 2024
 * Nivel: TERCERO     NRC: 1992
 *************************/
//ListaCircularDoble.cpp
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "ListaCircularDoble.h"
#include "Validaciones.cpp"
#include <iostream>
#include <iomanip> // Para formatear la salida de fechas
#include <ctime>

Validaciones validar;

//acceso al inicio de la lista
template <typename T>
Nodo<T>* ListaCircularDoble<T>::getCabeza() const {
    return cabeza;
}

// Constructor
template <typename T>
ListaCircularDoble<T>::ListaCircularDoble() : cabeza(nullptr) {}

// Destructor
template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    limpiar();
}


// Insertar un nodo en la lista
template <typename T>
void ListaCircularDoble<T>::insertar(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);
    if (cabeza == nullptr) {
        // Lista vacía: el nodo apunta a sí mismo
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        cabeza = nuevo;
    } else {
        Nodo<T>* ultimo = cabeza->getAnterior();

        // Actualizar punteros para el nuevo nodo
        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(ultimo);

        // Actualizar punteros de los nodos existentes
        ultimo->setSiguiente(nuevo);
        cabeza->setAnterior(nuevo);
    }
}

// Eliminar un nodo según un criterio
template <typename T>
void ListaCircularDoble<T>::eliminar(const int& opcion, const std::string& criterioA, const std::string& criterioB) {
    if (!cabeza) {
        return; // Lista vacía
    }

    Nodo<T>* actual = cabeza;
    Nodo<T>* inicio = cabeza; // Nodo inicial para referencia
    bool eliminado = false;   // Bandera para saber si eliminamos algún nodo

    do {
        Nodo<T>* siguiente = actual->getSiguiente(); // Guardar el siguiente nodo antes de realizar operaciones
        const T& elemento = actual->getDato();

        // Verificar criterios de eliminación
        if ((opcion == 1 && elemento.get_ISNB() == criterioA) ||  // Eliminar por ISBN
            (opcion == 2 && elemento.get_nombre_libro() == criterioA) ||  // Eliminar por nombre de libro
            (opcion == 3 && elemento.get_nombre_autor() == criterioA && elemento.get_apellido_autor() == criterioB)) {  // Eliminar por autor

            Nodo<T>* anterior = actual->getAnterior();
            Nodo<T>* siguiente = actual->getSiguiente();

            if (actual == cabeza && actual->getSiguiente() == cabeza) { // Caso especial: único nodo en la lista
                cabeza = nullptr;
            } else {
                anterior->setSiguiente(siguiente);
                siguiente->setAnterior(anterior);

                if (actual == cabeza) { // Actualizar cabeza si es necesario
                    cabeza = siguiente;
                }
            }

            delete actual; // Liberar memoria del nodo actual
            eliminado = true;

            // Actualizar la referencia de inicio si se elimina el nodo inicial
            if (actual == inicio) {
                inicio = siguiente;
            }

            actual = siguiente; // Mover al siguiente nodo
            continue; // Continuar al siguiente nodo sin avanzar automáticamente
        }

        actual = siguiente; // Mover al siguiente nodo solo si no se elimina
    } while (cabeza && actual != inicio); // Continuar mientras no volvamos al inicio

    // Mensaje solo si no se elimina ningún nodo
    if (!eliminado) {
        std::cerr << "No se encontró ningún elemento con los criterios especificados.\n";
    }
}

template <typename T>
void ListaCircularDoble<T>::eliminar_autor(const std::string& nombreAutor, const std::string& apellidoAutor) {
    if (!cabeza) {
        return; // Lista vacía
    }

    Nodo<T>* actual = cabeza;
    Nodo<T>* inicio = cabeza; // Nodo inicial para referencia
    bool eliminado = false; // Bandera para saber si eliminamos algún nodo

    do {
        Nodo<T>* siguiente = actual->getSiguiente(); // Guardar siguiente nodo antes de realizar operaciones
        const T& elemento = actual->getDato();

        // Verificar si el autor coincide
        if (elemento.get_nombre() == nombreAutor && elemento.get_apellido() == apellidoAutor) {
            Nodo<T>* anterior = actual->getAnterior();
            Nodo<T>* siguiente = actual->getSiguiente();

            // Caso especial: único nodo en la lista
            if (actual == cabeza && actual->getSiguiente() == cabeza) {
                cabeza = nullptr;
            } else {
                anterior->setSiguiente(siguiente);
                siguiente->setAnterior(anterior);

                if (actual == cabeza) { // Actualizar cabeza si es necesario
                    cabeza = siguiente;
                }
            }

            delete actual; // Liberar memoria del nodo actual
            eliminado = true;
        }

        actual = siguiente; // Mover al siguiente nodo

    } while (cabeza && actual != inicio); // Continuar mientras no volvamos al inicio

    // Si no se elimina ningún nodo, mostrar un mensaje opcional
    if (!eliminado) {
        std::cerr << "No se encontró ningún autor con los criterios especificados.\n";
    }
}


// Buscar un nodo
template <typename T>
void ListaCircularDoble<T>::buscar(const int& opcion, const std::string& criterioA, const std::string& criterioB) const {
    if (!cabeza) {
        std::cout << "Lista vacía.\n";
        return;
    }

    Nodo<T>* actual = cabeza;
    bool encontrado = false;

    do {
        const T& elemento = actual->getDato();

        // Opciones de búsqueda
        if ((opcion == 1 && elemento.get_ISNB() == criterioA) ||  // Búsqueda por ISNB
            (opcion == 2 && elemento.get_nombre_libro() == criterioA) ||  // Búsqueda por nombre de libro
            (opcion == 3 && elemento.get_nombre_autor() == criterioA && elemento.get_apellido_autor() == criterioB)) {  // Búsqueda por autor
            std::cout << "Elemento encontrado:\n"
                      << "Nombre del Libro: " << elemento.get_nombre_libro() << "\n"
                      << "ISNB: " << elemento.get_ISNB() << "\n"
                      << "Autor: " << elemento.get_nombre_autor() << " " << elemento.get_apellido_autor() << "\n";
            encontrado = true;
            break;
        }

        actual = actual->getSiguiente();
    } while (actual != cabeza);

    if (!encontrado) {
        std::cout << "No se encontró ningún elemento con los criterios especificados.\n";
    }
}

template <typename T>
void ListaCircularDoble<T>::buscar_autor(const std::string& nombreAutor, const std::string& apellidoAutor) const {
    if (!cabeza) {
        std::cout << "Lista vacía. No hay autores registrados.\n";
        return;
    }

    Nodo<T>* actual = cabeza;
    bool encontrado = false;

    do {
        const T& autor = actual->getDato(); // Obtener el dato del nodo actual

        // Comparar nombre y apellido del autor
        if (autor.get_nombre() == nombreAutor && autor.get_apellido() == apellidoAutor) {
            std::cout << "Autor encontrado:\n"
                      << "Nombre: " << autor.get_nombre() << " " << autor.get_apellido() << "\n"
                      << "Segundo Nombre: " << autor.get_segundo_nombre() << "\n"
                      << "Segundo Apellido: " << autor.get_segundo_apellido() << "\n"
                      << "Nacionalidad: " << autor.get_nacionalidad() << "\n"
                      << "Fecha de Nacimiento: " << autor.get_fecha_nacimiento_str() << "\n";
            encontrado = true;
            break; // Salir del bucle al encontrar al autor
        }

        actual = actual->getSiguiente(); // Pasar al siguiente nodo
    } while (actual != cabeza);

    if (!encontrado) {
        std::cout << "No se encontró ningún autor con el nombre y apellido especificados.\n";
    }
}


// Mostrar la lista
template <typename T>
void ListaCircularDoble<T>::mostrar() const {
    if (!cabeza) {
        std::cout << "Lista vacía.\n";
        return;
    }

    Nodo<T>* actual = cabeza;
    std::cout << "Lista de Libros:\n";

    do {
        const T& elemento = actual->getDato();
        std::cout << "Nombre del Libro: " << elemento.get_nombre_libro() 
                  << ", ISNB: " << elemento.get_ISNB() 
                  << ", Autor: " << elemento.get_nombre_autor() << " " << elemento.get_apellido_autor() 
                  << ", Fecha de Registro: " << elemento.get_fecha_registro_str() // Mostrar la fecha
                  << "\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}

template <typename T>
void ListaCircularDoble<T>::mostrar_autor() const {
    if (!cabeza) {
        std::cout << "Lista de autores vacía.\n";
        return;
    }

    Nodo<T>* actual = cabeza;
    std::cout << "Lista de Autores:\n";

    do {
        const T& autor = actual->getDato();

        std::time_t t = std::time(nullptr);
        tm fecha_actual = *std::localtime(&t);

        // Ajustar tm_year para incluir 1900
        int anio_actual = fecha_actual.tm_year + 1900;
        int anio_nacimiento = autor.get_fecha_nacimiento().tm_year + 1900;

        // Calcular la edad
        int edad = anio_actual - anio_nacimiento;

        
        // Ajustar si el autor aún no ha cumplido años este año
        if ((fecha_actual.tm_mon < autor.get_fecha_nacimiento().tm_mon) ||
            (fecha_actual.tm_mon == autor.get_fecha_nacimiento().tm_mon &&
             fecha_actual.tm_mday < autor.get_fecha_nacimiento().tm_mday)) {
            edad--;
        }

        std::cout << "Nombres del Autor: " << autor.get_nombre() << " "
                  << autor.get_segundo_nombre() << "\n"
                  << "Apellidos del Autor: " << autor.get_apellido()<< " "
                  << autor.get_segundo_apellido() << "\n"
                  << "Nacionalidad: " << autor.get_nacionalidad() << "\n"
                  << "Fecha de Nacimiento: " << autor.get_fecha_nacimiento_str() << "\n"
                  << "Edad: " << edad << " años\n";
        actual = actual->getSiguiente();
    } while (actual != cabeza);
}



// Limpiar la lista
template <typename T>
void ListaCircularDoble<T>::limpiar() {
    if (!cabeza) return;

    Nodo<T>* actual = cabeza;
    do {
        Nodo<T>* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);

    cabeza = nullptr;
}

template <typename T>
template <typename U>
void ListaCircularDoble<T>::validar_autor(const std::string& criterioA, const std::string& criterioB, ListaCircularDoble<U>& listaRelacionada) {
    Nodo<U>* actual = listaRelacionada.getCabeza();
    bool encontrado = false;

    if (!actual) {
        //std::cout << "La lista relacionada está vacía.\n";
    } else {
        do {
            const U& elemento = actual->getDato();
            // Verifica si criterioA y criterioB coinciden con los valores en la lista relacionada
            if (elemento.get_nombre() == criterioA && elemento.get_apellido() == criterioB) {
                encontrado = true;
                break;
            }
            actual = actual->getSiguiente();
        } while (actual != listaRelacionada.getCabeza());
    }

    if (encontrado) {
        //std::cout << "El elemento con criterios " << criterioA << " y " << criterioB << " ya está registrado.\n";
    } else {
        std::cout << "Alerta.\n";
        std::cout << "El autor " << criterioA << " " << criterioB << " no está en la base de datos.\n";
        std::cout << "Por favor, regístrelo.\n";

        // Solicitar datos para un nuevo elemento relacionado
        U nuevoElemento;
        tm fecha = {};
        std::string segundoNombre, segundoApellido, nacionalidad;

        std::cout << "Ingrese el segundo nombre del autor: ";
        segundoNombre=validar.ingresar_string2();

        std::cout << "Ingrese el segundo apellido del autor: ";
        segundoApellido=validar.ingresar_string2();

        std::cout << "Ingrese la nacionalidad del autor: ";
        nacionalidad=validar.ingresar_string();

        fecha=validar.ingresarFecha();


        // Configurar el nuevo elemento
        nuevoElemento.set_nombre(criterioA);
        nuevoElemento.set_apellido(criterioB);
        nuevoElemento.set_segundo_nombre(segundoNombre);
        nuevoElemento.set_segundo_apellido(segundoApellido);
        nuevoElemento.set_nacionalidad(nacionalidad);
        nuevoElemento.set_fecha_nacimiento(fecha);

        // Insertar el nuevo elemento en la lista relacionada
        listaRelacionada.insertar(nuevoElemento);

        std::cout << "El nuevo autor ha sido registrado exitosamente.\n";
    }
}

template <typename T>
void ListaCircularDoble<T>::verificar_INSB(std::string& insb) const {
    if (!cabeza) {
        // Si la lista está vacía, no hay conflicto de INSB
        return;
    }

    Nodo<T>* actual = cabeza;
    bool insbDuplicado;

    do {
        const T& elemento = actual->getDato();
        if (elemento.get_ISNB() == insb) {
            insbDuplicado = true;
            break;
        }
        actual = actual->getSiguiente();
        insbDuplicado = false;
    } while (actual != cabeza);

    // Mientras el INSB esté duplicado, solicita un nuevo INSB al usuario
    while (insbDuplicado) {
        std::cout << "ERRROR\n";
        std::cout << "El INSB ingresado (" << insb << ") ya está registrado en la lista.\n";
        std::cout << "Por favor, ingrese un nuevo INSB: ";
        insb=validar.validarISBN();

        // Reinicia la búsqueda para verificar el nuevo INSB
        actual = cabeza;
        do {
            const T& elemento = actual->getDato();
            if (elemento.get_ISNB() == insb) {
                insbDuplicado = true;
                break;
            }
            actual = actual->getSiguiente();
            insbDuplicado = false;
        } while (actual != cabeza);
    }
}

template <typename T>
void ListaCircularDoble<T>::guardarEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo, std::ios::out);

    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << " para escritura.\n";
        return;
    }

    Nodo<T>* actual = cabeza;

    if (!cabeza) {
        archivo.close();
        return;
    }

    do {
        archivo << actual->getDato() << "\n";  // Asume que los datos tienen sobrecargado el operador '<<'
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    archivo.close();
    //std::cout << "Lista guardada en " << nombreArchivo << " exitosamente.\n";
}

template <typename T>
void ListaCircularDoble<T>::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::in);

    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << " para lectura.\n";
        return;
    }

    limpiar(); // Limpia la lista actual para evitar datos duplicados al cargar

    T elemento;
    while (archivo >> elemento) {  // Asume que los datos tienen sobrecargado el operador '>>'
        insertar(elemento);       // Inserta cada elemento en la lista
    }

    archivo.close();
    //std::cout << "Lista cargada desde " << nombreArchivo << " exitosamente.\n";
}

//guardado en carpeta de back up
template <typename T>
void ListaCircularDoble<T>::guardarRespaldo() const {
    // Crear carpeta "respaldos" si no existe
    if (!std::filesystem::exists("respaldos")) {
        std::filesystem::create_directory("respaldos");
    }

    // Obtener la fecha y hora actuales
    std::time_t tiempo = std::time(nullptr);
    std::tm* fecha_local = std::localtime(&tiempo);

    // Formatear la fecha y hora
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M", fecha_local);

    // Crear nombre de archivo
    std::string nombreArchivo = "respaldos/respaldo_" + std::string(buffer) + ".txt";

    // Usar directamente la función guardarEnArchivo
    guardarEnArchivo(nombreArchivo);
    std::cout << "Respaldo guardado como: " << nombreArchivo << std::endl;
}

//desplegade de txts back up para recuperacio
template <typename T>
void ListaCircularDoble<T>::restaurarRespaldo() {
    std::vector<std::string> archivos;

    // Verificar si la carpeta "respaldos" existe
    if (!std::filesystem::exists("respaldos")) {
        std::cout << "La carpeta 'respaldos' no existe. No hay respaldos disponibles." << std::endl;
        return;
    }

    // Obtener los archivos de respaldo en la carpeta "respaldos"
    for (const auto& entry : std::filesystem::directory_iterator("respaldos")) {
        if (entry.is_regular_file()) {
            archivos.push_back(entry.path().string());
        }
    }

    if (archivos.empty()) {
        std::cout << "No hay respaldos disponibles en la carpeta 'respaldos'." << std::endl;
        return;
    }

    // Mostrar los archivos disponibles
    std::cout << "Archivos de respaldo disponibles:" << std::endl;
    for (int i = 0; i < archivos.size(); ++i) {
        std::cout << i + 1 << ". " << archivos[i] << std::endl;
    }

    // Solicitar al usuario que seleccione un archivo
    int seleccion;
    std::cout << "Seleccione el número del archivo de respaldo que desea restaurar: ";
    std::cin >> seleccion;

    if (seleccion < 1 || seleccion > archivos.size()) {
        std::cerr << "Selección no válida." << std::endl;
        return;
    }

    // Usar directamente el nombre del archivo con cargarDesdeArchivo
    cargarDesdeArchivo(archivos[seleccion - 1]);
    std::cout << "Respaldo restaurado desde: " << archivos[seleccion - 1] << std::endl;
}

template <typename T>
void ListaCircularDoble<T>::buscar_por_fecha(int anioInicio, int anioFin) const {
    if (!cabeza) {
        std::cout << "Lista vacía.\n";
        return;
    }

    // Convertir los años ingresados a objetos tm
    tm fechaInicio = {};
    tm fechaFin = {};

    fechaInicio.tm_year = anioInicio - 1900; // tm_year es el número de años desde 1900
    fechaInicio.tm_mon = 0; // Enero
    fechaInicio.tm_mday = 1; // Día 1

    fechaFin.tm_year = anioFin - 1900;
    fechaFin.tm_mon = 11; // Diciembre
    fechaFin.tm_mday = 31; // Día 31

    // Validar que el rango de fechas sea correcto
    if (difftime(mktime(&fechaFin), mktime(&fechaInicio)) < 0) {
        std::cerr << "Error: El año inicial debe ser menor o igual al año final.\n";
        return;
    }

    Nodo<T>* actual = cabeza; // Nodo inicial para recorrer la lista
    bool encontrado = false; // Indica si al menos un libro cumple con la condición

    while (true) {
        const T& elemento = actual->getDato();
        const tm& fechaRegistro = elemento.get_fecha_registro(); // Obtener la fecha del registro

        // Verificar si la fecha está dentro del rango especificado
        if (difftime(mktime(const_cast<tm*>(&fechaRegistro)), mktime(&fechaInicio)) >= 0 &&
            difftime(mktime(&fechaFin), mktime(const_cast<tm*>(&fechaRegistro))) >= 0) {
            // Imprimir información del libro
            std::cout << "Libro encontrado:\n"
                      << "Nombre del Libro: " << elemento.get_nombre_libro() << "\n"
                      << "ISNB: " << elemento.get_ISNB() << "\n"
                      << "Autor: " << elemento.get_nombre_autor() << " " << elemento.get_apellido_autor() << "\n"
                      << "Fecha de Registro: " << std::put_time(&fechaRegistro, "%Y-%m-%d") << "\n\n";
            encontrado = true; // Marcamos que al menos un libro fue encontrado
        }

        actual = actual->getSiguiente(); // Pasar al siguiente nodo

        // Verificar si hemos regresado al inicio de la lista
        if (actual == cabeza) {
            break;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron libros registrados entre las fechas especificadas.\n";
    }
}
