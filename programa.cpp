#include "programa.hpp"

#include "UI/pIniciarSesion.hpp"
#include "UI/pRegistrar.hpp"
#include "UI/pListaCursos.hpp"

#include <iostream>


Programa::Programa() {
    this->pantallaActual = nullptr;
    this->usuario = nullptr;

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
}

void Programa::quit() {
    running = false;
}

void Programa::cambiarPantalla(TIPO_PANTALLA pantalla) {
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
        case TIPO_PANTALLA::EDITAR_CURSO:

            break;
        case TIPO_PANTALLA::LISTA_USUARIOS:

            break;
        case TIPO_PANTALLA::EDITAR_USUARIO:

            break;
    }
}

void Programa::setUsuario(Usuario* usuario) {
    this->usuario = usuario;
}