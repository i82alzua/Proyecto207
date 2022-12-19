#include "pListaUsuarios.hpp"

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>
#include <string>
#include <limits>

PListaUsuarios::PListaUsuarios(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
    this->listaUsuarios = Almacenamiento::getInstancia()->obtenerTodosUsuarios();
}

void PListaUsuarios::recibirTecla(char c) {
    if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
        if (c == '1') {
            // Ver usuario
            std::cout << "\n\n";
            std::cout << "-------------------------------------\n";
            std::cout << "            VER UN USUARIO           \n";
            std::cout << "-------------------------------------\n\n";
            std::string dni;
            std::cout << "  Introduzca el DNI: ";
            std::cin >> dni;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
        else if (c == '2') {
            // Añadir usuario
             // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::cout << "\n\n";
            std::cout << "-------------------------------------\n";
            std::cout << "            ANADIR UN USUARIO           \n";
            std::cout << "-------------------------------------\n\n";
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
            Almacenamiento::getInstancia()->anadirUsuario(nombreUsuario, contrasena, dni, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_USUARIOS);
        }
        else if (c == '3') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
    else {
        if (c == '1') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
}

void PListaUsuarios::renderizar() {
    std::cout << "\n\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "              USUARIOS REGISTRADOS             \n";
    std::cout << "-----------------------------------------------\n\n";

    for (size_t i = 0; i < listaUsuarios.size(); i++) {
        std::string tipo = tipoUsuarioString((TIPO_USUARIO)listaUsuarios[i].getTipo());
        std::cout << tipo.append(23 - tipo.length(), ' ') << " " << listaUsuarios[i].getUsuario() << " " << listaUsuarios[i].getDNI() << std::endl;
    }

    std::cout << "\n\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "              OPCIONES DISPONIBLES            \n";
    std::cout << "----------------------------------------------\n\n";

    if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
        std::cout << "  1. Ver un usuario específico.\n"; // Ver tiene editar y eliminar
        std::cout << "  2. Anadir un nuevo usuario.\n";
        std::cout << "  3. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";    
    }
    else {
        std::cout << "  1. Volver." << std::endl;
    }
}