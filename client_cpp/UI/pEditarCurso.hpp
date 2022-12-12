#ifndef P_EDITAR_CURSO_HPP
#define P_EDITAR_CURSO_HPP

#include "pantalla.hpp"
#include "../DTO/curso.hpp"

class PEditarCurso : public Pantalla {
    public:
        PEditarCurso(Programa* programa, Usuario* usuario, Curso* curso);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        Curso* curso;

};

#endif