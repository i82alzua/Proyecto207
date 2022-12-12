#ifndef P_VER_CURSO_HPP
#define P_VER_CURSO_HPP

#include "pantalla.hpp"
#include "../DTO/curso.hpp"
#include "../DTO/recurso.hpp"

#include <vector>

class Programa;

class PVerCurso : public Pantalla {
    public:
        PVerCurso(Programa* programa, Usuario* usuario, int idcurso);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        Curso curso;
        std::vector<Recurso> recursos;

        bool inscrito;
        float ratioAprobados;
        float ratioAlcance;

};

#endif