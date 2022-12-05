#include "pListaCursos.hpp"

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>

PListaCursos::PListaCursos(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;

    // TODO: obtener cursos de la clase intermedia this->listaCursos = 
    this->listaCursos = Almacenamiento::getInstancia()->obtenerTodosCursos();
}

void PListaCursos::recibirTecla(char c) {
    
}

void PListaCursos::renderizar() {
    for (size_t i = 0; i < listaCursos.size(); i++) {
        // TODO: Añadir nombre
        std::cout << listaCursos[i].getIdCurso() << " " << listaCursos[i].getContenido() << std::endl;
    }
}