#include "visitante.hpp"

Visitante::Visitante() {

    this->direccionIP = 0;

}

Visitante::Visitante(int direccionIP) {

    this->direccionIP = 0;

}

void Visitante::setDireccionIP(int direccionIP) {

    this->direccionIP = direccionIP;

}

int Visitante::getDireccion() {

    return direccionIP;

}