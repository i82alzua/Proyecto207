#include "pVerUsuario.hpp"

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>
#include <limits>

PVerUsuario::PVerUsuario(Programa* programa, Usuario* usuario, const std::string& dni) {
    this->programa = programa;
    this->usuario = usuario;

    this->user = Almacenamiento::getInstancia()->obtenerUsuario(dni);
}

void PVerUsuario::recibirTecla(char c) {
    if (c == '1') {
        // Editar

        // Limpiar el buffer std::cin
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Pide los datos
        std::string nombre;
        std::cout << "Introduzca el nombre (en blanco para no editar): ";
        std::getline(std::cin, nombre);

        std::string contrasena;
        std::cout << "Introduzca la contrasena (en blanco para no editar): ";
        std::getline(std::cin, contrasena);

        // Hace la peticion a la API
        Almacenamiento::getInstancia()->editarUsuario(user.getDNI(), nombre, contrasena, programa->getSessionToken());
        std::string dni = user.getDNI();
        programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
    }
    else if (c == '2') {
        // Eliminar
        Almacenamiento::getInstancia()->eliminarUsuario(user.getDNI(), programa->getSessionToken());
        if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_USUARIOS);
        }
        else {
            programa->setSessionToken("");
            programa->setUsuario(nullptr);
            programa->cambiarPantalla(TIPO_PANTALLA::INICIAR_SESION);
        }
    }
    else if (c == '3') {
        // Volver
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }
}

void PVerUsuario::renderizar() {
    std::cout << "\n\n";

    std::cout << user.getDNI() << "\n";
    std::cout << user.getUsuario() << "\n";
    std::cout << tipoUsuarioString((TIPO_USUARIO)user.getTipo()) << "\n";

    std::cout << "\n";
    std::cout << "-----------------------------------" << std::endl;
    if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
        // Menu admin
        std::cout << "1. Editar estudiante\n";
        std::cout << "2. Eliminar estudiante\n";
        std::cout << "3. Volver" << std::endl;
    }
    else {
        // Menu resto usuarios
        std::cout << "1. Editar mis datos\n";
        std::cout << "2. Eliminar mi cuenta\n";
        std::cout << "3. Volver\n";
    }
}