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


    if ((usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) && user.getUsuario() == programa->getUsuario()->getUsuario()) {


        if (c == '1') {
            // Editar

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "            EDITAR MIS DATOS           \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  - En blando para no modificar -\n\n";
            std::cout << "  Nuevo usuario: ";
            std::getline(std::cin, nombre);

            std::string contrasena;
            std::cout << "  Nueva contraseña: ";
            std::getline(std::cin, contrasena);

            // Hace la peticion a la API
            Almacenamiento::getInstancia()->editarUsuario(user.getDNI(), nombre, contrasena, programa->getSessionToken());
            std::string dni = user.getDNI();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
 
        else if (c == '2') {
            // Volver
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
        

    }

    else if (usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::ESTUDIANTE){

        if (c == '1') {
            // Editar

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "              EDITAR DATOS             \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  - En blanco para no modificar -\n\n";
            std::cout << "  Nuevo usuario: ";
            std::getline(std::cin, nombre);

            std::string contrasena;
            std::cout << "  Nueva contraseña: ";
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

    else {


        if (c == '1') {
            // Editar

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "            EDITAR MIS DATOS           \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  - En blando para no modificar -\n\n";
            std::cout << "  Nuevo usuario: ";
            std::getline(std::cin, nombre);

            std::string contrasena;
            std::cout << "  Nueva contraseña: ";
            std::getline(std::cin, contrasena);

            // Hace la peticion a la API
            Almacenamiento::getInstancia()->editarUsuario(user.getDNI(), nombre, contrasena, programa->getSessionToken());
            std::string dni = user.getDNI();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
 
        else if (c == '2') {
            // Volver
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }


    }

}


void PVerUsuario::renderizar() {
    std::cout << "\n\n";

    std::cout << user.getDNI() << "\n";
    std::cout << user.getUsuario() << "\n";
    std::cout << tipoUsuarioString((TIPO_USUARIO)user.getTipo()) << "\n";

    std::cout << "\n\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "              OPCIONES DISPONIBLES            \n";
    std::cout << "----------------------------------------------\n\n";

    if ((usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS)&& user.getUsuario() == programa->getUsuario()->getUsuario()) {
      
        std::cout << "  1. Editar mis datos.\n";
        std::cout << "  2. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";

    }
    else if (usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::ESTUDIANTE) {
     
        std::cout << "  1. Editar datos.\n";
        std::cout << "  2. Eliminar estudiante\n";
        std::cout << "  3. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }

    else {
      
        std::cout << "  1. Editar mis datos.\n";
        std::cout << "  2. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";

    }

}