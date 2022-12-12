#include "pIniciarSesion.hpp"

#include "enumPantallas.hpp"
#include "../programa.hpp"

#include "../DTO/usuario.hpp"
#include "../DTO/enumUsuarios.hpp"

#include "../almacenamiento.hpp"

#include <iostream>
#include <limits>


PIniciarSesion::PIniciarSesion(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
}

void PIniciarSesion::recibirTecla(char c) {
    if (c == '1') { // Iniciar sesion
        // Limpiar el buffer std::cin
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Pide los datos
        std::string nombre;
        std::cout << "Introduzca el nombre de usuario: ";
        std::getline(std::cin, nombre);

        std::string contrasena;
        std::cout << "Introduzca la contrasena: ";
        std::getline(std::cin, contrasena);
        

        LoginResponse response = Almacenamiento::getInstancia()->login(nombre, contrasena);
        if (response.token != "") {
            programa->setUsuario(response.user);
            programa->setSessionToken(response.token);
        }
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }
    else if (c == '2') { // Registrar
        programa->cambiarPantalla(TIPO_PANTALLA::REGISTRAR);
    }
    else if (c == '3') { // Entrar como visitante
        std::string usuario = "";
        std::string contrasena = "";
        std::string dni = "";
        programa->setUsuario(new Usuario(usuario, contrasena, dni, TIPO_USUARIO::VISITANTE));
        programa->setSessionToken("");
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }
}

void PIniciarSesion::renderizar() {
    std::cout << "--------------------------------\n";
    std::cout << "           BIENVENIDO           \n";
    std::cout << "--------------------------------\n\n";
    std::cout << "1. Iniciar sesion\n";
    std::cout << "2. Registrar nueva cuenta\n";
    std::cout << "3. Entrar como visitante" << std::endl;
}