#include "estadisticas.hpp"

Estadisticas::Estadisticas() {

    this->porcentajeAprobados = 0;
    this->numeroInscritos = 0;
    this->porcentajeAlcance = 0;

}

Estadisticas::Estadisticas(int porcentajeAprobados, int numeroInscritos, int porcentajeAlcance) {

    this->porcentajeAprobados = porcentajeAprobados;
    this->numeroInscritos = numeroInscritos;
    this->porcentajeAlcance = porcentajeAlcance;

}

void Estadisticas::setPorcentajeAprobados(int porcentajeAprobados) {

    this->porcentajeAprobados = porcentajeAprobados;

}

int Estadisticas::getPorcentajeAprobados() {

    return porcentajeAprobados;

}

void Estadisticas::setNumeroInscritos(int numeroInstritos) {

    this->numeroInscritos = numeroInscritos;

}

int Estadisticas::getNumeroInscritos() {

    return numeroInscritos;

}

void Estadisticas::setPorcentajeAlcance(int porcentajeAlcance) {

    this->porcentajeAlcance = porcentajeAlcance;

}

int Estadisticas::getPorcentajeAlcance() {

    return porcentajeAlcance;

}