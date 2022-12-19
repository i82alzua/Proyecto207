#ifndef RECURSO_HPP
#define RECURSO_HPP

#include <string>

class Recurso {
    public:
        Recurso();
        Recurso(const std::string& aula, int capacidad);
        Recurso(int id, const std::string& aula, int capacidad);

        int getId();
        
        void setAula(const std::string& aula);
        std::string getAula();

        void setCapacidad(int capacidad);
        int getCapacidad();

    private:
        int id;
        std::string aula;
        int capacidad;
};

#endif