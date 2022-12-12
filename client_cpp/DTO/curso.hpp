#ifndef COURSE_HPP
#define COURSE_HPP

#include <string>
#include <vector>

class Curso {
    public:
        Curso();
        Curso(const std::string& nombreCurso, int idCurso, const std::string& contenido, const std::vector<std::string>& listaMatriculados, const std::string& fechaInicio, const std::string& fechaFin);
        Curso(const std::string& nombreCurso, int idCurso, const std::string& contenido, const std::vector<std::string>& listaMatriculados, const std::string& fechaInicio, const std::string& fechaFin, const std::string& ponente);

        void setIdCurso(int id);
        int getIdCurso();

        //pasamos las cadenas como const std::string& (referencia constante) para que no se copie en memoria la cadena. Más óptimo
        void setNombreCurso(const std::string& nombreCurso);
        std::string getNombreCurso();
        
        void setContenido(const std::string& contenido);
        std::string getContenido();

        void setListaMatriculados(const std::vector<std::string>& listaMatriculados);
        std::vector<std::string> getListaMatriculados();

        void setFechaInicio(const std::string& fechaInicio);
        std::string getFechaInicio();

        void setFechaFin(const std::string& fechaFin);
        std::string getFechaFin();
        
        void setPonente(const std::string& ponente);
        std::string getPonente();

    private:
        std::string nombreCurso;
        int idCurso;
        std::string contenido;
        std::vector<std::string> listaMatriculados;
        std::string fechaInicio;
        std::string fechaFin;
        std::string ponente;
};

#endif