#include "pListaRecursos.hpp"

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>
#include <string>
#include <limits>

PListaRecursos::PListaRecursos(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;
    this->listaRecursos = Almacenamiento::getInstancia()->obtenerTodosRecursos();
}

void PListaRecursos::recibirTecla(char c) {
    if (usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        if (c == '1') {
            // Crear recurso
            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::cout << "\n\n";
            std::cout << "---------------------\n";
            std::cout << "  ANADIR UN RECURSO  \n";
            std::cout << "---------------------\n\n";
            std::string aula;
            std::cout << "  Aula: ";
            std::getline(std::cin, aula);

            int capacidad;
            std::cout << "  Capacidad: ";
            std::cin >> capacidad;

            Almacenamiento::getInstancia()->crearRecurso(aula, capacidad, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_RECURSOS);
        }
        else if (c == '2') {
            // Editar recurso
             // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::cout << "\n\n";
            std::cout << "----------------------------------------\n";
            std::cout << "          MODIFICAR UN RECURSO          \n";
            std::cout << "----------------------------------------\n\n";
            std::string strId;
            std::cout << "  ID del recurso a modificar: ";
            std::getline(std::cin, strId);
            int id = atoi(strId.c_str());
            std::cout << "  - En blando para no modificar -\n";

            std::string aula;
            std::cout << "  Aula: ";
            std::getline(std::cin, aula);

            std::string strCapacidad;
            std::cout << "  Capacidad: ";
            std::getline(std::cin, strCapacidad);
            int capacidad = atoi(strCapacidad.c_str());

            Almacenamiento::getInstancia()->editarRecurso(id, aula, capacidad, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_RECURSOS);
        }
        else if (c == '3') {
            // Eliminar recurso
            int id;
            std::cout << "\n\n";
            std::cout << "----------------------------------\n";
            std::cout << "       MODIFICAR UN RECURSO       \n";
            std::cout << "----------------------------------\n\n";
            std::cout << " ID del recurso a modificar: ";
            std::cin >> id;
            Almacenamiento::getInstancia()->eliminarRecurso(id, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_RECURSOS);
        }
        else if (c == '4') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
    else {
        if (c == '1') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
}

void PListaRecursos::renderizar() {
    std::cout << "\n\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "              RECURSOS DISPONIBLES             \n";
    std::cout << "-----------------------------------------------\n\n";
    
    for (size_t i = 0; i < listaRecursos.size(); i++) {
        std::cout << "ID: " << listaRecursos[i].getId() << " Aula: " << listaRecursos[i].getAula() << " Capacidad: (" << listaRecursos[i].getCapacidad() << ")\n";
    }

    std::cout << "\n\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "              OPCIONES DISPONIBLES            \n";
    std::cout << "----------------------------------------------\n\n";

    if (usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        std::cout << "  1. Crear nuevo recurso.\n";
        std::cout << "  2. Editar recurso existente.\n";
        std::cout << "  3. Eliminar recurso existente.\n";
        std::cout << "  4. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";    
    }
    else {
        std::cout << "  1. Volver" << std::endl;
    }
}