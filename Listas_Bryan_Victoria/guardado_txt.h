#ifndef GUARDADO_TXT_H
#define GUARDADO_TXT_H

#include <string>
#include "Lista_Simple.h"
#include "Persona.h"

class guardado_txt {

public:
    static void guardar(const std::string& nombreArchivo, Lista_Simple<Persona>& listaPersonas);
    static void buscarPorCriterio(const std::string& nombreArchivo, const std::string& criterio);
    static void EliminarPorCriterioEnArchivo(const std::string& nombreArchivo, const std::string& criterio, const std::string& valor);
    static void MostrarListasDesdeArchivo(const std::string& nombreArchivo);
};

#endif
