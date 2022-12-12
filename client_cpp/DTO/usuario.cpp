#include "usuario.hpp"

Usuario::Usuario() {

    this->usuario = "";
    this->contrasena = "";
    this->dni = "";
    this->tipo = TIPO_USUARIO::ESTUDIANTE;

}

Usuario::Usuario(const std::string& usuario, const std::string& contrasena, const std::string& dni, TIPO_USUARIO tipo) {

    this->usuario = usuario;
    this->contrasena = contrasena;
    this->dni = dni;
    this->tipo = tipo;

}
        
void Usuario::setUsuario(const std::string& usuario) {

    this->usuario = usuario;

}

std::string Usuario::getUsuario() {

    return usuario;

}

void Usuario::setContasena(const std::string& contrasena) {

    this->contrasena = contrasena;   

}

std::string Usuario::getContrasena() {

    return contrasena;

}

void Usuario::setDNI(const std::string& dni) {
    this->dni = dni;
}

std::string Usuario::getDNI() {
    return dni;
}


void Usuario::setTipo(TIPO_USUARIO tipo) {

    this->tipo = tipo;   

}

int Usuario::getTipo() {

    return tipo;

}

