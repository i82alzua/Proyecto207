#ifndef P_REGISTRAR_HPP
#define P_REGISTRAR_HPP

#include "pantalla.hpp"

class Programa;

class PRegistrar : public Pantalla {
    public:
        PRegistrar(Programa* programa, Usuario* usuario);

        void recibirTecla(char c) override;
        void renderizar() override;

    private:
        Usuario* nuevoUsuario;

};

#endif