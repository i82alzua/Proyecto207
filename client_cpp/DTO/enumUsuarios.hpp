#ifndef ENUM_USUARIOS_HPP
#define ENUM_USUARIOS_HPP

#include <string>

enum TIPO_USUARIO {
    VISITANTE = 0,
    ESTUDIANTE = 1,
    COORDINADOR_CURSOS = 2,
    COORDINADOR_RECURSOS = 3,
    ADMIN = 4
};

std::string tipoUsuarioString(TIPO_USUARIO tipo);

#endif