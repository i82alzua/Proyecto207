#include "pRegistrar.hpp"

#include "../programa.hpp"
#include "../DTO/usuario.hpp"
#include "../DTO/enumUsuarios.hpp"

#include "../almacenamiento.hpp"

#include <iostream>
#include <limits>

PRegistrar::PRegistrar(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
}

void PRegistrar::recibirTecla(char c) {
    programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
}

void PRegistrar::renderizar() {
    // Limpiar el buffer std::cin
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Pide los datos
    std::cout << "\n\n";
    std::cout << "-------------------------------\n";
    std::cout << "          REGISTRARSE          \n";
    std::cout << "-------------------------------\n\n";
    std::string nombreUsuario;
    std::cout << "  Usuario: ";
    std::getline(std::cin, nombreUsuario);

    std::string contrasena;
    std::cout << "  Contrasena: ";
    std::getline(std::cin, contrasena);

    std::string dni;
    std::cout << "  DNI: ";
    std::getline(std::cin, dni);
    
    
    //TODO: Registrar en BD
    LoginResponse response = Almacenamiento::getInstancia()->registrarUsuario(nombreUsuario, contrasena, dni);
    if (response.token != "") {
        programa->setUsuario(response.user);
        programa->setSessionToken(response.token);
        std::cout << "\n\n";
        std::cout << "Usuario registrado correctamente!" << std::endl;
    }
    else {
        std::cout << "¡ Hubo algun error !\n\n" << std::endl;
    }

    std::cout << "Pulse cualquier tecla para continuar.";
}