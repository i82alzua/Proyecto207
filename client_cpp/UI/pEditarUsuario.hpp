#ifndef P_EDITAR_USUARIO_HPP
#define P_EDITAR_USUARIO_HPP

#include "pantalla.hpp"
#include "../DTO/curso.hpp"
#include "../DTO/usuario.hpp"

class PEditarUsuario : public Pantalla {
    public:
        PEditarUsuario(Programa* programa, Usuario* usuario);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:

};

#endif