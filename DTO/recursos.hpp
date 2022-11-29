#ifndef RECURSO_HPP
#define RECURSO_HPP

#include <string>

class Recurso {
    public:
        Recurso();
        Recurso(const std::string& aula, int capacidad);

        void setAula(const std::string& aula);
        std::string getAula();

        void setCapacidad(int capacidad);
        int getCapacidad();

    private:
        std::string aula;
        int capacidad;
};

#endif