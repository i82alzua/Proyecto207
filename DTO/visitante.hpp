#ifndef VISITANTE_HPP
#define VISITANTE_HPP

#include <string>

class Visitante {

    public:
        Visitante();
        Visitante(int direccionIP);

        void setDireccionIP(int direccionIP);
        int getDireccion();

    private:
        int direccionIP;

};

#endif