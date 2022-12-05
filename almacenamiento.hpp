#ifndef ALMACENAMIENTO_HPP
#define ALMACENAMIENTO_HPP

#include "DTO/curso.hpp"

#include <vector>

class Almacenamiento {
    public:
        Almacenamiento(Almacenamiento &other) = delete; // Evita clonar
        void operator=(const Almacenamiento &) = delete; // Evita asignar

        static Almacenamiento* getInstancia();

        std::vector<Curso> obtenerTodosCursos();

    protected:
        Almacenamiento() {}
};

static Almacenamiento* instancia;

#endif