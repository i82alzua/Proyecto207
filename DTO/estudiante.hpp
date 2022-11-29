#ifndef ESTUDIANTE_HPP
#define ESTUDIANTE_HPP

#include <string>

class Estudiante {

    public:
        Estudiante();
        Estudiante(int DNI);
        void setDNI(int DNI);
        int getDNI();

    private:
        int DNI;

};

#endif