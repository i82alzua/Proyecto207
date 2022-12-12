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

        std::cout << "Introduzca el nombre del curso: ";
        std::cin >> nombreCurso;
        std::cout << "Introduzca el ID del curso";
        std::cin >> idCurso;
        std::cout << "Introduzca el contenido del curso: ";
        std::cin >> contenido;
        std::cout << "Introduzca la fecha de inicio del curso: ";
        std::cin >> fechaInicio;
        std::cout << "Introduzca la fecha de fin del curso: ";
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
            std::cout << "Curso no válido !!" << std::endl;
        }
    
    }

    else if (c == '2') { // Eliminar un curso.
        int ID;
        std::cout << "Introduzca el ID del curso que desea eliminar." << std::endl;
        std::cin >> ID;
        
        //TODO, funcion que traiga, si existe, el curso con el id introducido
        // almacenamiento->eliminarCurso();
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }

    else if (c == '3') { // Modificar curso existente.
        int ID;
        std::cout << "Introduzca el ID del curso que desea modificar" << std::endl;
        std::cin >> ID;
        
        //TODO, funcion que modifique el curso indicado por ID
        // alacenamiento->modificarCurso();
        programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
    }
}

void PEditarCurso::renderizar() {
    std::cout << "Elija una opcion:" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "1. Añadir un curso" << std::endl;
    std::cout << "2. Eliminar un curso" << std::endl;
    std::cout << "3. Modificar un curso existente" << std::endl;
}