#ifndef TESTS_2_HPP
#define TESTS_2_HPP

#include "../vendor/cute/cute.h"

#include "../almacenamiento.hpp"
#include "../DTO/curso.hpp"


void test_create_course () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_course", "1234");

    std::string courseName = "my_test_course";
    std::vector<Curso> courses = Almacenamiento::getInstancia()->obtenerTodosCursos();
    bool exists = false;
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].getNombreCurso() == courseName) {
            exists = true;
            break;
        }
    }

    ASSERT_EQUAL(exists, false);

    Almacenamiento::getInstancia()->crearCurso(courseName, "", "2022-01-01", "2022-12-01", "yo", login.token);

    courses = Almacenamiento::getInstancia()->obtenerTodosCursos();
    exists = false;
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].getNombreCurso() == courseName) {
            exists = true;
            break;
        }
    }


    ASSERT_EQUAL(exists, true);

}

void test_delete_course () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_admin", "1234");

    std::string courseName = "my_test_course";
    std::vector<Curso> courses = Almacenamiento::getInstancia()->obtenerTodosCursos();
    int courseId = 0;
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].getNombreCurso() == courseName) {
            courseId = courses[i].getIdCurso();
            break;
        }
    }

    ASSERT_NOT_EQUAL_TO(courseId, 0);

    Almacenamiento::getInstancia()->eliminarCurso(courseId, login.token);

    courses = Almacenamiento::getInstancia()->obtenerTodosCursos();
    bool exists = false;
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].getNombreCurso() == courseName) {
            exists = true;
            break;
        }
    }


    ASSERT_EQUAL(exists, false);

}

#endif