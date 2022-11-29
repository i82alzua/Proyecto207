#include "curso.hpp"

Curso::Curso() {
    this->idCurso = 0;
    this->contenido = "";
    this->listaMatriculados = std::vector<std::string>();
    this->fechaInicio = "";
    this->fechaFin = "";
}

Curso::Curso(int idCurso, const std::string& contenido, const std::vector<std::string>& listaMatriculados, const std::string& fechaInicio, const std::string& fechaFin) {
    this->idCurso = idCurso;
    this->contenido = contenido;
    this->listaMatriculados = listaMatriculados;
    this->fechaInicio = fechaInicio;
    this->fechaFin = fechaFin;
}

Curso::Curso(int idCurso, const char* contenido, const std::vector<std::string>& listaMatriculados, const char* fechaInicio, const char* fechaFin) {
    this->idCurso = idCurso;
    this->contenido = std::string(contenido);
    this->listaMatriculados = listaMatriculados;
    this->fechaInicio = std::string(fechaInicio);
    this->fechaFin = std::string(fechaFin);
}


void Curso::setIdCurso(int id) {
    this->idCurso = id;
}
int Curso::getIdCurso() {
    return idCurso;
}

void Curso::setContenido(const std::string& contenido) {
    this->contenido = contenido;
}
std::string Curso::getContenido() {
    return contenido;
}

void Curso::setListaMatriculados(const std::vector<std::string>& listaMatriculados) {
    this->listaMatriculados = listaMatriculados;
}
std::vector<std::string> Curso::getListaMatriculados() {
    return listaMatriculados;
}

void Curso::setFechaInicio(const std::string& fechaInicio) {
    this->fechaInicio = fechaInicio;
}
std::string Curso::getFechaInicio() {
    return fechaInicio;
}

void Curso::setFechaFin(const std::string& fechaFin) {
    this->fechaFin = fechaFin;
}
std::string Curso::getFechaFin() {
    return fechaInicio;
}