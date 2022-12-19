#ifndef P_VER_USUARIO_HPP
#define P_VER_USUARIO_HPP

#include "pantalla.hpp"
#include "../DTO/usuario.hpp"

class Programa;

class PVerUsuario : public Pantalla {
    public:
        PVerUsuario(Programa* programa, Usuario* usuario, const std::string& dni);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        int idusuario;
        Usuario user;

};

#endif