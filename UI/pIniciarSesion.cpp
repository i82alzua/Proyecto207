#include "pIniciarSesion.hpp"

#include <iostream>

#include "enumPantallas.hpp"
#include "../programa.hpp"

#include "../DTO/usuario.hpp"
#include "../DTO/enumUsuarios.hpp"


PIniciarSesion::PIniciarSesion(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
}

void PIniciarSesion::recibirTecla(char c) {
    if (c == '1') { // Iniciar sesion
        std::string usuario;
        std::string contrasena;
        
        std::cout << "Introduzca usuario: ";
        std::cin >> usuario;
        std::cout << "Introduzca contrasena: ";
        std::cin >> contrasena;

        // TODO:
        // - Traernos de BD el todo usuario con mismmo username
        // - Comprobar si contraseñas coinciden
        Usuario* u;
        // u = getFromDatabase();
        if (true) {
            programa->setUsuario(u);
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
        else {
            std::cout << "Usuario no valido!" << std::endl;
        }
    }
    else if (c == '2') { // Registrar
        programa->cambiarPantalla(TIPO_PANTALLA::REGISTRAR);
    }
    else if (c == '3') { // Entrar como visitante
        std::string usuario = "";
        std::string contrasena = "";
        std::string dni = "";
        programa->setUsuario(new Usuario(usuario, contrasena, dni, TIPO_USUARIO::VISITANTE));
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }
}

void PIniciarSesion::renderizar() {
    std::cout << "Elija una opcion:" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "1. Iniciar sesion" << std::endl;
    std::cout << "2. Registrar nueva cuenta" << std::endl;
    std::cout << "3. Entrar como visitante" << std::endl;
}