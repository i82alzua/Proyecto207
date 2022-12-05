#ifndef P_LISTA_USUARIOS_HPP
#define P_LISTA_USUARSOS_HPP

#include "pantalla.hpp"
#include <vector>
#include "../DTO/curso.hpp"

class Programa;

class PListaUsuarios : public Pantalla {
    public:
        PListaUsuarios();

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        std::vector<Usuario> listaUsuarios;