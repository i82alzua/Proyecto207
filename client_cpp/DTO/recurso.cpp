#include "recurso.hpp"

Recurso::Recurso() {
    this->aula = "";
    this->capacidad = 0;
}
Recurso::Recurso(const std::string& aula, int capacidad) {
    this->aula = aula;
    this->capacidad = capacidad;
}
Recurso::Recurso(int id, const std::string& aula, int capacidad) {
    this->id = id;
    this->aula = aula;
    this->capacidad = capacidad;
}

int Recurso::getId() {
    return id;
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