#include "pRegistrar.hpp"

#include "../programa.hpp"
#include "../DTO/usuario.hpp"
#include "../DTO/enumUsuarios.hpp"

#include <iostream>

PRegistrar::PRegistrar(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
    this->nuevoUsuario = nullptr;
}

void PRegistrar::recibirTecla(char c) {
    programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
}

void PRegistrar::renderizar() {
    std::string nombreUsuario;
    std::string contrasena;
    std::string dni;

    std::cout << "Introduzca nombre de usuario" << std::endl;
    std::cin >> nombreUsuario;

    std::cout << "Introduzca contrasena" << std::endl;
    std::cin >> contrasena;

    std::cout << "Introduzca dni" << std::endl;
    std::cin >> dni;

    nuevoUsuario = new Usuario(nombreUsuario, contrasena, dni, TIPO_USUARIO::ESTUDIANTE);
    
    //TODO: Registrar en BD
    
    programa->setUsuario(nuevoUsuario);
    std::cout << "Usuario registrado correctamente! Pulse cualquier tecla:";
}