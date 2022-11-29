#include "estudiante.hpp"

Estudiante::Estudiante() {

    this->DNI = 0;

}

Estudiante::Estudiante(int DNI) {

    this->DNI = DNI;

}

void Estudiante::setDNI(int DNI) {

    this->DNI = DNI;

}

int Estudiante::getDNI() {

    return DNI;

}