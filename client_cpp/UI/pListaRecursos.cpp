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
            std::string aula;
            std::cout << "Introduzca el nombre del aula: ";
            std::getline(std::cin, aula);

            int capacidad;
            std::cout << "Introduzca la capacidad: ";
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
            std::string strId;
            std::cout << "Introduzca la id del recurso: ";
            std::getline(std::cin, strId);
            int id = atoi(strId.c_str());

            std::string aula;
            std::cout << "Introduzca el nombre del aula: ";
            std::getline(std::cin, aula);

            std::string strCapacidad;
            std::cout << "Introduzca la capacidad: ";
            std::getline(std::cin, strCapacidad);
            int capacidad = atoi(strCapacidad.c_str());

            Almacenamiento::getInstancia()->editarRecurso(id, aula, capacidad, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_RECURSOS);
        }
        else if (c == '3') {
            // Eliminar recurso
            int id;
            std::cout << "Introduzca la id del recurso: ";
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
    std::cout << "Recursos\n"; 
    std::cout << "-----------------------------------\n";
    
    for (size_t i = 0; i < listaRecursos.size(); i++) {
        std::cout << listaRecursos[i].getId() << " " <<
                     listaRecursos[i].getAula() << " (" <<
                     listaRecursos[i].getCapacidad() << ")\n";
    }

    std::cout << "\n";
    std::cout << "-----------------------------------" << std::endl;
    if (usuario->getTipo() == TIPO_USUARIO::ADMIN || usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        std::cout << "1. Crear recurso\n";
        std::cout << "2. Editar recurso\n";
        std::cout << "3. Eliminar recurso\n";
        std::cout << "4. Volver" << std::endl;
    }
    else {
        std::cout << "1. Volver" << std::endl;
    }
}