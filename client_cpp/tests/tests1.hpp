#ifndef TESTS_1_HPP
#define TESTS_1_HPP

#include "../vendor/cute/cute.h"

#include "../almacenamiento.hpp"
#include "../DTO/usuario.hpp"
#include "../DTO/curso.hpp"


void test_enroll () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_student", "1234");

    // Vemos si estamos inscritos en este curso
    Curso course = Almacenamiento::getInstancia()->obtenerCurso(7);
    bool inscrito = false;
    for (size_t i = 0; i < course.getListaMatriculados().size(); i++) {
        if (course.getListaMatriculados()[i] == login.user->getUsuario()) {
            inscrito = true;
            break;
        }
    }
    
    ASSERT_EQUAL(inscrito, false);

    Almacenamiento::getInstancia()->inscribirEnCurso(7, "31874482T", login.token);

    // Vemos si estamos inscritos en este curso
    course = Almacenamiento::getInstancia()->obtenerCurso(7);
    inscrito = false;
    for (size_t i = 0; i < course.getListaMatriculados().size(); i++) {
        if (course.getListaMatriculados()[i] == login.user->getUsuario()) {
            inscrito = true;
            break;
        }
    }

    ASSERT_EQUAL(inscrito, true);

}

void test_unenroll () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_student", "1234");

    // Vemos si estamos inscritos en este curso
    Curso course = Almacenamiento::getInstancia()->obtenerCurso(7);
    bool inscrito = false;
    for (size_t i = 0; i < course.getListaMatriculados().size(); i++) {
        if (course.getListaMatriculados()[i] == login.user->getUsuario()) {
            inscrito = true;
            break;
        }
    }
    
    ASSERT_EQUAL(inscrito, true);

    Almacenamiento::getInstancia()->desinscribirEnCurso(7, "31874482T", login.token);

    // Vemos si estamos inscritos en este curso
    course = Almacenamiento::getInstancia()->obtenerCurso(7);
    inscrito = false;
    for (size_t i = 0; i < course.getListaMatriculados().size(); i++) {
        if (course.getListaMatriculados()[i] == login.user->getUsuario()) {
            inscrito = true;
            break;
        }
    }

    ASSERT_EQUAL(inscrito, false);

}

#endif