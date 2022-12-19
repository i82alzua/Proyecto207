#ifndef P_INICIAR_SESION_HPP
#define P_INICIAR_SESION_HPP

#include "pantalla.hpp"

class PIniciarSesion : public Pantalla {
    public:
        PIniciarSesion(Programa* programa, Usuario* usuario);

        void recibirTecla(char c) override;
        void renderizar() override;

};

#endif