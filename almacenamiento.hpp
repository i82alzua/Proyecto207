#ifndef ALMACENAMIENTO_HPP
#define ALMACENAMIENTO_HPP

#include "DTO/curso.hpp"
#include "../DTO/usuario.hpp"

#include <vector>

class Almacenamiento {
    public:
        Almacenamiento(Almacenamiento &other) = delete; // Evita clonar
        void operator=(const Almacenamiento &) = delete; // Evita asignar
        
        static Almacenamiento* getInstancia();

        std::vector<Curso> obtenerTodosCursos();

        // TODO
        void añadirCurso(Curso* curso);
        void eliminarCurso();
        void modificarCurso();
        // TODO
        void añadirUsuario(Usuario* usuario);
        void eliminarUsuario();
        void modificarUsuario();
        // TODO
        void getCursoFromDataBase();
        void getUsuarioFromDataBase();

    protected:
        Almacenamiento() {}
};

static Almacenamiento* instancia;

#endif