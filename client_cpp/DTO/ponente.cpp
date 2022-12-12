#include "ponente.hpp"

Ponente::Ponente() {
    this->nombre = "";
}
Ponente::Ponente(const std::string& nombre) {
    this->nombre = nombre;
}

void Ponente::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}
std::string Ponente::getNombre() {
    return nombre;
}