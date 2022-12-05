#include "pListaUsuarios.hpp"""

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>

PListaUsuarios::PListaUsuarios() {
    // TODO: obtener cursos de la clase intermedia this->listaCursos = 
}

void PListaCursos::recibirTecla(char c) {
    
}

void PListaCursos::renderizar() {
    // TODO, funcion que imprima el listado de usuarios, aunque no se si es una nueva o la lista de matriculados
    for (size_t i = 0; i < listaUsuarios.size(); i++) {
        // TODO, no comprendo el DNI en usuario y en estudiante, me sobra uno
        std::cout << listaUsuarios[i].getUsuario() << " " << listaUsuarios[i].getDNI() << std::endl;
    }
}