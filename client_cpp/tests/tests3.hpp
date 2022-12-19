#ifndef TESTS_3_HPP
#define TESTS_3_HPP

#include "../vendor/cute/cute.h"

#include "../almacenamiento.hpp"
#include "../DTO/usuario.hpp"
#include "../DTO/recurso.hpp"


void test_edit_user () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_admin", "1234");

    Usuario userOld = Almacenamiento::getInstancia()->obtenerUsuario("31874485T");
    Almacenamiento::getInstancia()->editarUsuario("31874485T", "test_user_modified", "", login.token);
    Usuario userNew = Almacenamiento::getInstancia()->obtenerUsuario("31874485T");

    ASSERT_NOT_EQUAL_TO(userOld.getUsuario(), userNew.getUsuario());

    Almacenamiento::getInstancia()->editarUsuario("31874485T", userOld.getUsuario(), "", login.token);
    Usuario userNew2 = Almacenamiento::getInstancia()->obtenerUsuario("31874485T");

    ASSERT_EQUAL(userOld.getUsuario(), userNew2.getUsuario());
}

void test_create_resource () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_resource", "1234");

    std::string classroom = "aulaPrueba";
    int capacity = 80;

    std::vector<Recurso> resources = Almacenamiento::getInstancia()->obtenerTodosRecursos();
    bool exists = false;
    for (size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getAula() == classroom && resources[i].getCapacidad() == capacity) {
            exists = true;
            break;
        }
    }

    ASSERT_EQUAL(exists, false);

    Almacenamiento::getInstancia()->crearRecurso(classroom, capacity, login.token);

    resources = Almacenamiento::getInstancia()->obtenerTodosRecursos();
    exists = false;
    for (size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getAula() == classroom && resources[i].getCapacidad() == capacity) {
            exists = true;
            break;
        }
    }


    ASSERT_EQUAL(exists, true);

}

void test_delete_resource () {
    LoginResponse login = Almacenamiento::getInstancia()->login("test_resource", "1234");

    std::string classroom = "aulaPrueba";
    int capacity = 80;
    int idx = -1;

    std::vector<Recurso> resources = Almacenamiento::getInstancia()->obtenerTodosRecursos();
    bool exists = false;
    for (size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getAula() == classroom && resources[i].getCapacidad() == capacity) {
            idx = i;
            break;
        }
    }

    ASSERT_NOT_EQUAL_TO(idx, -1);

    Almacenamiento::getInstancia()->eliminarRecurso(resources[idx].getId(), login.token);

    resources = Almacenamiento::getInstancia()->obtenerTodosRecursos();
    exists = false;
    for (size_t i = 0; i < resources.size(); i++) {
        if (resources[i].getAula() == classroom && resources[i].getCapacidad() == capacity) {
            exists = true;
            break;
        }
    }


    ASSERT_EQUAL(exists, false);

}

#endif