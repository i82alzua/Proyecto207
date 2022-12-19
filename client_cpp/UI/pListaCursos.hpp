#ifndef P_LISTA_CURSOS_HPP
#define P_LISTA_CURSOS_HPP

#include "pantalla.hpp"
#include <vector>
#include "../DTO/curso.hpp"

class Programa;

class PListaCursos : public Pantalla {
    public:
        PListaCursos(Programa* programa, Usuario* usuario);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        std::vector<Curso> listaCursos;

};

#endif