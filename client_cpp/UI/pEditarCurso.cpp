#include "pEditarCurso.hpp"

#include <iostream>

#include "enumPantallas.hpp"
#include "../programa.hpp"

#include "../DTO/usuario.hpp"
#include "../DTO/enumUsuarios.hpp"
#include "../DTO/curso.hpp"
#include "../almacenamiento.hpp"


PEditarCurso::PEditarCurso(Programa* programa, Usuario* usuario, Curso* curso) {
    this->programa = programa;
    this->usuario = usuario;
    this->curso = curso;
}

void PEditarCurso::recibirTecla(char c) {
    if (c == '1') { //  Añadir un curso
        std::string nombreCurso;
        int idCurso;
        std::string contenido;
        std::vector<std::string> listaMatriculados;
        std::string fechaInicio;
        std::string fechaFin;

        std::cout << "\n\n";
        std::cout << "---------------------------------------\n";
        std::cout << "            ANADIR UN CURSO            \n";
        std::cout << "---------------------------------------\n\n";
        std::cout << "  Nombre: ";
        std::cin >> nombreCurso;
        std::cout << "  ID: ";
        std::cin >> idCurso;
        std::cout << "  Contenido: ";
        std::cin >> contenido;
        std::cout << "  Fecha de inicio: ";
        std::cin >> fechaInicio;
        std::cout << "  Fecha de fin: ";
        std::cin >> fechaFin;

        Curso* c = new Curso(nombreCurso, idCurso, contenido, listaMatriculados, fechaInicio, fechaFin);
       
        //TODO, funcion que compruebe si el curso ya existe en la BBDD
        Curso* curso;
        // curso = (almacenamiento->getCursoFromDataBase());

        if(curso->getIdCurso() != idCurso) {
            // almacenamiento->anandirCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
        else {
            std::cout << "¡ Curso no válido !" << std::endl;
        }
    
    }

    else if (c == '2') { // Eliminar un curso.
        int ID;

        std::cout << "\n\n";
        std::cout << "-----------------------------------\n";
        std::cout << "         ELIMINAR UN CURSO         \n";
        std::cout << "-----------------------------------\n\n";
        std::cout << "  ID del curso a eliminar: ";
        std::cin >> ID;
    
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }

    else if (c == '3') { // Modificar curso existente.
        int ID;
        std::cout << "\n\n";
        std::cout << "------------------------------------\n";
        std::cout << "         MODIFICAR UN CURSO         \n";
        std::cout << "------------------------------------\n\n";       
        std::cout << "  Id del curos a modificar: ";
        std::cin >> ID;
    
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }
}

void PEditarCurso::renderizar() {
    std::cout << "------------------------------------\n";
    std::cout << "          SOBRE LOS CURSOS          \n";
    std::cout << "------------------------------------\n\n";
    std::cout << "  1. Anadir un curso.\n";
    std::cout << "  2. Eliminar un curso.\n"; 
    std::cout << "  3. Modificar un curso existente.\n\n";
    std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
}