#include "programa.hpp"
#include "almacenamiento.hpp"

#include "UI/pIniciarSesion.hpp"
#include "UI/pRegistrar.hpp"
#include "UI/pListaCursos.hpp"
#include "UI/pVerCurso.hpp"
#include "UI/pVerUsuario.hpp"
#include "UI/pListaUsuarios.hpp"
#include "UI/pListaRecursos.hpp"

#include <iostream>


Programa::Programa() {
    this->pantallaActual = nullptr;

    //TODO: Crear destructor para liberar pantalla y usuario
}

void Programa::init() {
    running = true;
    cambiarPantalla(TIPO_PANTALLA::INICIAR_SESION);

    while (running) {
        if (pantallaActual == nullptr) {
            std::cout << "ERROR: No hay pantalla actual" << std::endl;
            break;
        }

        pantallaActual->renderizar();
        
        char c;
        std::cin >> c; 
        
        pantallaActual->recibirTecla(c);
    }

    Almacenamiento::getInstancia()->logout(sessionToken);
    delete pantallaActual;
    delete usuario;
    sessionToken = "";
}

void Programa::quit() {
    running = false;
}

void Programa::cambiarPantalla(TIPO_PANTALLA pantalla, void* arg) {
    delete pantallaActual;
    pantallaActual = nullptr;

    switch (pantalla) {
        case TIPO_PANTALLA::INICIAR_SESION:
            pantallaActual = (Pantalla*)(new PIniciarSesion(this, usuario));
            break;
        case TIPO_PANTALLA::REGISTRAR:
            pantallaActual = (Pantalla*)(new PRegistrar(this, usuario));
            break;
        case TIPO_PANTALLA::LISTA_CURSOS:
            pantallaActual = (Pantalla*)(new PListaCursos(this, usuario));
            break;
        case TIPO_PANTALLA::VER_CURSO:
            pantallaActual = (Pantalla*)(new PVerCurso(this, usuario, *((int*)arg)));
            break;
        case TIPO_PANTALLA::LISTA_USUARIOS:
            pantallaActual = (Pantalla*)(new PListaUsuarios(this, usuario));
            break;
        case TIPO_PANTALLA::VER_USUARIO:
            pantallaActual = (Pantalla*)(new PVerUsuario(this, usuario, *((std::string*)arg)));
            break;
        case TIPO_PANTALLA::LISTA_RECURSOS:
            pantallaActual = (Pantalla*)(new PListaRecursos(this, usuario));
            break;
    }
}


Usuario* Programa::getUsuario() {
    return this->usuario;
}

void Programa::setUsuario(Usuario* usuario) {
    this->usuario = usuario;
}

std::string Programa::getSessionToken() {
    return sessionToken;
}

void Programa::setSessionToken(const std::string& token) {
    this->sessionToken = token;
}