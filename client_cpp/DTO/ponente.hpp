#ifndef PONENTE_HPP
#define PONENTE_HPP

#include <iostream>

class Ponente {
    public:
        Ponente();
        Ponente(const std::string& nombre);

        void setNombre(const std::string& nombre);
        std::string getNombre();

    private:
        std::string nombre;
};

#endif