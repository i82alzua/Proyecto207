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
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "              VER UN CURSO             \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Crear curso
            std::string nombre;
            int idCurso;
            std::string contenido;
            std::vector<std::string> listaMatriculados;
            std::string fechaInicio;
            std::string fechaFin;
            std::string ponente;

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "            AÑADIR UN CURSO            \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Nombre: ";
            std::cin >> nombre;
            std::cout << "  ID: ";
            std::cin >> idCurso;
            std::cout << "  Contenido: ";
            std::cin >> contenido;
            std::cout << "  Fecha inicio: ";
            std::cin >> fechaInicio;
            std::cout << "  Fecha fin: ";
            std::cin >> fechaFin;
            std::cout << "  Ponente: ";
            std::cin >> ponente;

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
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "              VER UN CURSO             \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Introduzca el numero del curso: ";
            std::cin >> idCurso;
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&idCurso));
        }
        else if (c == '2') {
            // Crear curso
            std::string nombre;
            int idCurso;
            std::string contenido;
            std::vector<std::string> listaMatriculados;
            std::string fechaInicio;
            std::string fechaFin;
            std::string ponente;

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "            ANADIR UN CURSO            \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Nombre: ";
            std::cin >> nombre;
            std::cout << "  ID: ";
            std::cin >> idCurso;
            std::cout << "  Contenido: ";
            std::cin >> contenido;
            std::cout << "  Fecha de inicio: ";
            std::cin >> fechaInicio;
            std::cout << "  Fecha de fin: ";
            std::cin >> fechaFin;
            std::cout << "  Ponente: ";
            std::cin >> ponente;

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
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "              VER UN CURSO             \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Introduzca el numero del curso: ";
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
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "              VER UN CURSO             \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Introduzca el numero del curso: ";
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
            std::cout << "\n\n";
            std::cout << "---------------------------------------\n";
            std::cout << "              VER UN CURSO             \n";
            std::cout << "---------------------------------------\n\n";
            std::cout << "  Introduzca el numero del curso: ";
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
    std::cout << "---------------------------------------------\n";
    std::cout << "              CURSOS DISPONIBLES             \n";
    std::cout << "---------------------------------------------\n\n";

    for (size_t i = 0; i < listaCursos.size(); i++) {
        std::cout << "ID: " << listaCursos[i].getIdCurso() << " Nombre: " << listaCursos[i].getNombreCurso() << " Contenido: " << listaCursos[i].getContenido() << std::endl;
    }

    std::cout << "\n\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "              OPCIONES DISPONIBLES            \n";
    std::cout << "----------------------------------------------\n\n";

    if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
        std::cout << "  1. Ver un curso específico.\n";
        std::cout << "  2. Crear un nuevo curso.\n";
        std::cout << "  3. Ver mi perfil.\n";
        std::cout << "  4. Gestionar usuarios del sistema.\n";
        std::cout << "  5. Ver recursos disponibles.\n";
        std::cout << "  6. Cerrar sesión.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS) {
        std::cout << "  1. Ver un curso específico.\n";
        std::cout << "  2. Crear un nuevo curso.\n";
        std::cout << "  3. Ver mi perfil.\n";
        std::cout << "  4. Cerrar sesión.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        std::cout << "  1. Ver un curso específico.\n";
        std::cout << "  2. Ver recursos disponibles.\n";
        std::cout << "  3. Ver mi perfil.\n";
        std::cout << "  4. Cerrar sesión.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }
    else if (usuario->getTipo() == TIPO_USUARIO::VISITANTE) {
        std::cout << "  1. Ver un curso específico.\n";
        std::cout << "  2. Salir.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }
    else {
        std::cout << "  1. Ver un curso específico.\n";
        std::cout << "  2. Ver mi perfil.\n";
        std::cout << "  3. Cerrar sesión.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }
}