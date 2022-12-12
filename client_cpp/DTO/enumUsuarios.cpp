#include "enumUsuarios.hpp"

std::string tipoUsuarioString(TIPO_USUARIO tipo) {
    switch(tipo) {
        case TIPO_USUARIO::VISITANTE:
            return std::string("Visitante");
            break;
        case TIPO_USUARIO::ESTUDIANTE:
            return std::string("Estudiante");
            break;
        case TIPO_USUARIO::COORDINADOR_CURSOS:
            return std::string("Coordinador de cursos");
            break;
        case TIPO_USUARIO::COORDINADOR_RECURSOS:
            return std::string("Coordinador de recursos");
            break;
        case TIPO_USUARIO::ADMIN:
            return std::string("Admin");
            break;
    }

    return "";
}