#ifndef P_LISTA_RECURSOS_HPP
#define P_LISTA_RECURSOS_HPP

#include "pantalla.hpp"
#include "../DTO/recurso.hpp"
#include "../programa.hpp"

#include <vector>

class Programa;

class PListaRecursos : public Pantalla {
    public:
        PListaRecursos(Programa* programa, Usuario* usuario);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        std::vector<Recurso> listaRecursos;
};

#endif