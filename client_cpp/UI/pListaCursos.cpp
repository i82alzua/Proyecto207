#include "pListaCursos.hpp"

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>
#include <limits>

PListaCursos::PListaCursos(Programa* programa, Usuario* usuario) {
    this->programa = programa;
    this->usuario = usuario;

    this->listaCursos = Almacenamiento::getInstancia()->obtenerTodosCursos();
}

void PListaCursos::recibirTecla(char c) {
    if (programa->getUsuario()->getTipo() == TIPO_USUARIO::ADMIN) {
        // Menu admin
        if (c == '1') {
            // Ver curso
            int idCurso = 0;
            std::cout << "Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Crear curso

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::cout << "Introduzca el nombre: ";
            std::getline(std::cin, nombre);

            std::string contenido;
            std::cout << "Introduzca el contenido: ";
            std::getline(std::cin, contenido);

            std::string fechaInicio;
            std::cout << "Introduzca la fecha de inicio (YYYY-MM-DD): ";
            std::getline(std::cin, fechaInicio);

            std::string fechaFin;
            std::cout << "Introduzca la fecha de fin (YYYY-MM-DD): ";
            std::getline(std::cin, fechaFin);

            std::string ponente;
            std::cout << "Introduzca el ponente: ";
            std::getline(std::cin, ponente);

            // Hace la peticion a la API
            Almacenamiento::getInstancia()->crearCurso(nombre, contenido, fechaInicio, fechaFin, ponente, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
        else if (c == '3') {
            // Modificar mis datos
            std::string dni = usuario->getDNI();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
        else if (c == '4') {
            // Gestionar usuarios
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_USUARIOS);
        }
        else if (c == '5') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_RECURSOS);
        }
        else if (c == '6') {
            // Cerrar sesion
            programa->quit();
        }
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS) {
        if (c == '1') {
            // Ver curso
            int idCurso = 0;
            std::cout << "Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Crear curso
            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::cout << "Introduzca el nombre: ";
            std::getline(std::cin, nombre);

            std::string contenido;
            std::cout << "Introduzca el contenido: ";
            std::getline(std::cin, contenido);

            std::string fechaInicio;
            std::cout << "Introduzca la fecha de inicio (YYYY-MM-DD): ";
            std::getline(std::cin, fechaInicio);

            std::string fechaFin;
            std::cout << "Introduzca la fecha de fin (YYYY-MM-DD): ";
            std::getline(std::cin, fechaFin);

            std::string ponente;
            std::cout << "Introduzca el ponente: ";
            std::getline(std::cin, ponente);

            // Hace la peticion a la API
            Almacenamiento::getInstancia()->crearCurso(nombre, contenido, fechaInicio, fechaFin, ponente, programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
        else if (c == '3') {
            // Modificar mis datos
            std::string dni = usuario->getDNI();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
        else if (c == '4') {
            // Cerrar sesion
            programa->quit();
        }
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        if (c == '1') {
            // Ver curso
            int idCurso = 0;
            std::cout << "Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Crear curso
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_RECURSOS);
        }
        else if (c == '3') {
            // Modificar mis datos
            std::string dni = usuario->getDNI();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
        else if (c == '4') {
            // Cerrar sesion
            programa->quit();
        }
    }
    else if (usuario->getTipo() == TIPO_USUARIO::VISITANTE) {
        // Menu visitante
        if (c == '1') {
            // Ver curso
            int idCurso = 0;
            std::cout << "Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Cerrar sesion
            programa->quit();
        }
    }
    else {
        // Menu demas usuarios
        if (c == '1') {
            // Ver curso
            int idCurso = 0;
            std::cout << "Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Modificar mis datos
            std::string dni = usuario->getDNI();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_USUARIO, (void*)(&dni));
        }
        else if (c == '3') {
            // Cerrar sesion
            programa->quit();
        }
    }
}

void PListaCursos::renderizar() {
    std::cout << "\n\n"; 
    std::cout << "Cursos\n"; 
    std::cout << "-----------------------------------\n";

    for (size_t i = 0; i < listaCursos.size(); i++) {
        // TODO: Añadir nombre
        std::cout <<
            listaCursos[i].getIdCurso() << " " << 
            listaCursos[i].getNombreCurso() << " " <<
            listaCursos[i].getContenido() << std::endl;
    }

    std::cout << "\n";
    std::cout << "-----------------------------------" << std::endl;
    if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
        std::cout << "1. Ver curso\n";
        std::cout << "2. Crear curso\n";
        std::cout << "3. Ver mi perfil\n";
        std::cout << "4. Gestionar usuarios\n";
        std::cout << "5. Ver recursos\n";
        std::cout << "6. Cerrar sesion" << std::endl;
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS) {
        std::cout << "1. Ver curso\n";
        std::cout << "2. Crear curso\n";
        std::cout << "3. Ver mi perfil\n";
        std::cout << "4. Cerrar sesion" << std::endl;
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        std::cout << "1. Ver curso\n";
        std::cout << "2. Ver recursos\n";
        std::cout << "3. Ver mi perfil\n";
        std::cout << "4. Cerrar sesion" << std::endl;
    }
    else if (usuario->getTipo() == TIPO_USUARIO::VISITANTE) {
        std::cout << "1. Ver curso\n";
        std::cout << "2. Cerrar sesion" << std::endl;
    }
    else {
        std::cout << "1. Ver curso\n";
        std::cout << "2. Ver mi perfil\n";
        std::cout << "3. Cerrar sesion" << std::endl;
    }
}