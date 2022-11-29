#ifndef ESTADISTICAS_HPP
#define ESTADISTICAS_HPP

#include <string>

class Estadisticas {

    public:
        Estadisticas();
        Estadisticas(int porcentajeAprobados, int numeroInstritos, int porcentajeAlcance);
        
        void setPorcentajeAprobados(int porcentajeAprobados);
        int getPorcentajeAprobados();
        void setNumeroInscritos(int numeroInstritos);
        int getNumeroInscritos();
        void setPorcentajeAlcance(int porcentajeAlcance);
        int getPorcentajeAlcance();

    private:
        int porcentajeAprobados;
        int numeroInscritos;
        int porcentajeAlcance;

};

#endif