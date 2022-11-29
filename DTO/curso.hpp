#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>

class Curso {
    public:
        Curso();
        Curso(int idCurso, const std::string& contenido, const std::vector<std::string>& listaMatriculados, const std::string& fechaInicio, const std::string& fechaFin);
        Curso(int idCurso, const char* contenido, const std::vector<std::string>& listaMatriculados, const char* fechaInicio, const char* fechaFin);

        void setIdCurso(int id);
        int getIdCurso();

        //pasamos las cadenas como const std::string& (referencia constante) para que no se copie en memoria la cadena. Más óptimo
        void setContenido(const std::string& contenido);
        std::string getContenido();

        void setListaMatriculados(const std::vector<std::string>& listaMatriculados);
        std::vector<std::string> getListaMatriculados();

        void setFechaInicio(const std::string& fechaInicio);
        std::string getFechaInicio();

        void setFechaFin(const std::string& fechaFin);
        std::string getFechaFin();

    private:
        //TODO: Añadir nombre
        int idCurso;
        std::string contenido;
        std::vector<std::string> listaMatriculados;
        std::string fechaInicio;
        std::string fechaFin;
};

#endif