#include "pEditarUsuario.hpp"

#include <iostream>

#include "enumPantallas.hpp"
#include "../programa.hpp"

#include "../DTO/usuario.hpp"
#include "../DTO/enumUsuarios.hpp"
#include "../DTO/curso.hpp"
#include "../almacenamiento.hpp"


PEditarUsuario::PEditarUsuario(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
}

void PEditarUsuario::recibirTecla(char c) {
    if (c == '1') { //  Añadir un usuario

        Usuario* u;
        std::string usuario;
        std::string contrasena;
        std::string dni;
        int tipo_int;
        TIPO_USUARIO tipo;

        std::cout << "\n\n";
        std::cout << "--------------------------\n";
        std::cout << "       ANADIR USUARIO     \n";
        std::cout << "--------------------------\n\n";
        std::cout << "  Usuario: ";
        std::cin >> usuario;
        std::cout << "  Contrasena:";
        std::cin >> contrasena;
        std::cout << "  DNI: ";
        std::cin >> dni;
        std::cout << "  Tipo: ";
        std::cin >> tipo_int;
        tipo = (TIPO_USUARIO)tipo_int;

        u = new Usuario(usuario, contrasena, dni, tipo);
       
        //TODO, funcion que compruebe si el curso ya existe en la BBDD
        Usuario* user;
        // usuario = (Almacenamiento::getInstancia()->getUsuarioFromDataBase());

        if(user->getDNI() != dni) {
            // Almacenamiento::getInstancia()->anadirUsuario();
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_USUARIOS);
        }
        else {
            std::cout << "¡ Usuario no válido !" << std::endl;
        }
    
    }

    else if (c == '2') { // Eliminar un curso.
        int DNI;
        std::cout << "\n\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "             ELIMINAR UN USUARIO             \n";
        std::cout << "---------------------------------------------\n\n";
        std::cout << "  DNI del usuario a eliminar: ";
        std::cin >> DNI;
        
        //TODO, funcion que traiga, si existe, el curso con el id introducido
        // Almacenamiento::getInstancia()->eliminarUsuario();
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_USUARIOS);
    }

    else if (c == '3') { // Modificar curso existente.
        int ID;
        std::cout << "----------------------------------------------\n";
        std::cout << "             MODIFICAR UN USUARIO             \n";
        std::cout << "----------------------------------------------\n\n";
        std::cout << "  DNI del usuario a modificar: ";
        std::cin >> ID;
        
        //TODO, funcion que modifique el curso indicado por ID
        // Almacenamiento::getInstancia()->modificarUsuario();
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_USUARIOS);
    }
}

void PEditarUsuario::renderizar() {
    std::cout << "--------------------------------------\n";
    std::cout << "          SOBRE LOS USUARIOS          \n";
    std::cout << "--------------------------------------\n\n";
    std::cout << "  1. Anadir un usuario.\n";
    std::cout << "  2. Eliminar un usuario.\n";
    std::cout << "  3. Modificar un usuario existente.\n\n";
    std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
}