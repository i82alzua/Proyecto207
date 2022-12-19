#include "pVerCurso.hpp"

#include "../programa.hpp"
#include "../almacenamiento.hpp"

#include <iostream>
#include <limits>

PVerCurso::PVerCurso(Programa* programa, Usuario* usuario, int idcurso) {
    this->programa = programa;
    this->usuario = usuario;

    // Cargamos el curso via API
    this->curso = Almacenamiento::getInstancia()->obtenerCurso(idcurso);

    // Cargamos los recursos via API
    this->recursos = Almacenamiento::getInstancia()->obtenerRecursosCurso(idcurso);

    // Cargamos las estadisticas del curso
    CourseStats stats = Almacenamiento::getInstancia()->getCourseStats(idcurso);
    this->ratioAprobados = stats.ratioAprobados;
    this->ratioAlcance = stats.ratioAlcance;

    // Vemos si estamos inscritos en este curso
    this->inscrito = false;
    for (size_t i = 0; i < curso.getListaMatriculados().size(); i++) {
        if (curso.getListaMatriculados()[i] == usuario->getUsuario()) {
            this->inscrito = true;
            break;
        }
    }
}

void PVerCurso::recibirTecla(char c) {
    if (usuario->getTipo() == TIPO_USUARIO::ESTUDIANTE) {
        // Menu estudiantes
        if (c == '1') {
            if (inscrito) {
                // Desinscribirse
                Almacenamiento::getInstancia()->desinscribirEnCurso(curso.getIdCurso(), usuario->getDNI(), programa->getSessionToken());
                int id = curso.getIdCurso();
                programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
            }
            else {
                // Inscribirse
                Almacenamiento::getInstancia()->inscribirEnCurso(curso.getIdCurso(), usuario->getDNI(), programa->getSessionToken());
                int id = curso.getIdCurso();
                programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
            }

        }
        else if (c == '2') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
    else if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {
        if (c == '1') {
            // Editar

            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::string contenido;
            std::string fechaInicio;
            std::string fechaFin;
            std::string ponente;

            std::cout << "\n\n";
            std::cout << "------------------------------------------\n";
            std::cout << "            MODIFICAR UN CURSO            \n";
            std::cout << "------------------------------------------\n\n";
            std::cout << "  - En blando para no modificar -\n";
            std::cout << "  Nuevo nombre: ";
            std::getline(std::cin, nombre);
            std::cout << "  Nuevo contenido: ";
            std::getline(std::cin, contenido);
            std::cout << "  Nueva fecha de inicio (YYYY-MM-DD): ";
            std::getline(std::cin, fechaInicio);
            std::cout << "  Nueva fecha de fin (YYYY-MM-DD): ";
            std::getline(std::cin, fechaFin);
            std::cout << "  Nuevo ponente: ";
            std::getline(std::cin, ponente);

            // Hace la peticion a la API
            Almacenamiento::getInstancia()->editarCurso(curso.getIdCurso(), nombre, contenido, fechaInicio, fechaFin, ponente, programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '2') {
            // Eliminar
            Almacenamiento::getInstancia()->eliminarCurso(curso.getIdCurso(), programa->getSessionToken());
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
        else if (c == '3') {
            // Matricular
            std::cout << "\n\n";
            std::cout << "--------------------------------------------------\n";
            std::cout << "              MATRICULAR UN ESTUDIANTE            \n";
            std::cout << "--------------------------------------------------\n\n";
            std::string dni;
            std::cout << "  DNI del estudiante a matricular: ";
            std::cin >> dni;

            Almacenamiento::getInstancia()->inscribirEnCurso(curso.getIdCurso(), dni, programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
            
        }
        else if (c == '4') {
            // Desmatricular
            std::cout << "\n\n";
            std::cout << "-----------------------------------------------------\n";
            std::cout << "              DESMATRICULAR UN ESTUDIANTE            \n";
            std::cout << "-----------------------------------------------------\n\n";
            std::string dni;
            std::cout << "  DNI del estudiante a desmatricular: ";
            std::cin >> dni;

            Almacenamiento::getInstancia()->desinscribirEnCurso(curso.getIdCurso(), dni, programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '5') {
            // Asignar recurso
            int resourceid;
            std::cout << "\n\n";
            std::cout << "----------------------------------\n";
            std::cout << "          ASIGNAR RECURSOS        \n";
            std::cout << "----------------------------------\n\n";
            std::cout << "  ID del recurso a asignar: ";
            std::cin >> resourceid;

            Almacenamiento::getInstancia()->asignarRecurso(curso.getIdCurso(), resourceid, programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '6') {
            // Desasignar recurso
            Almacenamiento::getInstancia()->desasignarRecurso(curso.getIdCurso(), programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '7') {
            // Volver
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS) {
        if (c == '1') {
            // Editar
            // Limpiar el buffer std::cin
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Pide los datos
            std::string nombre;
            std::string contenido;
            std::string fechaInicio;
            std::string fechaFin;
            std::string ponente;

            std::cout << "\n\n";
            std::cout << "------------------------------------------\n";
            std::cout << "            MODIFICAR UN CURSO            \n";
            std::cout << "------------------------------------------\n\n";
            std::cout << "  - En blando para no modificar -\n";
            std::cout << "  Nuevo nombre: ";
            std::getline(std::cin, nombre);
            std::cout << "  Nuevo contenido: ";
            std::getline(std::cin, contenido);
            std::cout << "  Nueva fecha de inicio (YYYY-MM-DD): ";
            std::getline(std::cin, fechaInicio);
            std::cout << "  Nueva fecha de fin (YYYY-MM-DD): ";
            std::getline(std::cin, fechaFin);
            std::cout << "  Nuevo ponente: ";
            std::getline(std::cin, ponente);

            // Hace la peticion a la API
            Almacenamiento::getInstancia()->editarCurso(curso.getIdCurso(), nombre, contenido, fechaInicio, fechaFin, ponente, programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '2') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        if (c == '1') {
            // Asignar recurso
            int resourceid;
            std::cout << "\n\n";
            std::cout << "----------------------------------\n";
            std::cout << "          ASIGNAR RECURSOS        \n";
            std::cout << "----------------------------------\n\n";
            std::cout << "  ID del recurso a asignar: ";
            std::cin >> resourceid;

            Almacenamiento::getInstancia()->asignarRecurso(curso.getIdCurso(), resourceid, programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '2') {
            // Desasignar recurso
            Almacenamiento::getInstancia()->desasignarRecurso(curso.getIdCurso(), programa->getSessionToken());
            int id = curso.getIdCurso();
            programa->cambiarPantalla(TIPO_PANTALLA::VER_CURSO, (void*)(&id));
        }
        else if (c == '3') {
            // Volver
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
    else {
        if (c == '1') {
            programa->cambiarPantalla(TIPO_PANTALLA::LISTA_CURSOS);
        }
    }
}

void PVerCurso::renderizar() {
    std::cout << "\n\n"; 
    std::cout << "-----------------------------------\n";
    std::cout << curso.getNombreCurso() << "\n"; 
    std::cout << "-----------------------------------\n\n";

    std::cout << curso.getPonente() << "        " << curso.getFechaInicio() << " - " << curso.getFechaFin() << "\n";
    std::cout << curso.getContenido() << "\n";
    std::cout << "Porcentaje aprobados: " << (ratioAprobados * 100) << "%" << "\t";
    std::cout << "Alcance: " << (ratioAlcance * 100) << "%" << std::endl;

    std::cout << "\nMatriculados:                    Recursos:\n";
    int biggerSize = std::max(curso.getListaMatriculados().size(), recursos.size());
    for (int i = 0; i < biggerSize; i++) {
        if (i < curso.getListaMatriculados().size()) {
            std::cout << curso.getListaMatriculados()[i];
            std::string spacer(33 - curso.getListaMatriculados()[i].length(), ' ');
            std::cout << spacer;
        }
        else {
            std::string spacer(33, ' ');
            std::cout << spacer;
        }

        if (i < recursos.size()) {
            std::cout << recursos[i].getAula() << " (" <<
                         recursos[i].getCapacidad() << ")";
        }

        std::cout << "\n";
    }
    std::cout << std::endl;

    if (usuario->getTipo() == TIPO_USUARIO::ESTUDIANTE) {
        // Menu estudiantes
        std::cout << "\n\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "              OPCIONES DISPONIBLES            \n";
        std::cout << "----------------------------------------------\n\n";
        if (!inscrito) {
            std::cout << "  1. Matricularme en este curso.\n";
        }
        else {
            std::cout << "  1. Anular mi matriculacion en este curso.\n";
        }
        std::cout << "  2. Volver." << std::endl;
    }
    else if (usuario->getTipo() == TIPO_USUARIO::ADMIN) {

        std::cout << "\n\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "              OPCIONES DISPONIBLES            \n";
        std::cout << "----------------------------------------------\n\n";
        std::cout << "  1. Editar un curso existente.\n";
        std::cout << "  2. Eliminar un curso existente.\n";
        std::cout << "  3. Matricular a un alumno en un curso.\n";
        std::cout << "  4. Desmatricular a un alumno de un curso.\n";
        std::cout << "  5. Asignar recurso.\n";
        std::cout << "  6. Desasignar recurso.\n";
        std::cout << "  7. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";

    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_CURSOS) {
        std::cout << "\n\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "              OPCIONES DISPONIBLES            \n";
        std::cout << "----------------------------------------------\n\n";
        std::cout << "  1. Editar curso\n";
        std::cout << "  2. Volver\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";

    }
    else if (usuario->getTipo() == TIPO_USUARIO::COORDINADOR_RECURSOS) {
        std::cout << "\n\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "              OPCIONES DISPONIBLES            \n";
        std::cout << "----------------------------------------------\n\n";
        std::cout << "  1. Asignar recurso\n";
        std::cout << "  2. Desasignar recurso\n";
        std::cout << "  3. Volver.\n\n";
        std::cout << "Introduzca el número de la opción que desee llevar a cabo: ";
    }
    else {
        std::cout << "\n\n";
        std::cout << "----------------------------------------------\n";
        std::cout << "              OPCIONES DISPONIBLES            \n";
        std::cout << "----------------------------------------------\n\n";
        std::cout << "  1. Volver" << std::endl;
    }
}
