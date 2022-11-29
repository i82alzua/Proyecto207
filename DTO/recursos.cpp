#include "recursos.hpp"

Recurso::Recurso() {
    this->aula = "";
    this->capacidad = 0;
}
Recurso::Recurso(const std::string& aula, int capacidad) {
    this->aula = aula;
    this->capacidad = capacidad;
}

void Recurso::setAula(const std::string& aula) {
    this->aula = aula;
}
std::string Recurso::getAula() {
    return aula;
}

void Recurso::setCapacidad(int capacidad) {
    this->capacidad = capacidad;
}
int Recurso::getCapacidad() {
    return capacidad;
}