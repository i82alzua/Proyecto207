#ifndef ALMACENAMIENTO_HPP
#define ALMACENAMIENTO_HPP

#include "DTO/curso.hpp"
#include "DTO/usuario.hpp"
#include "DTO/recurso.hpp"

#include <string>
#include <vector>

struct LoginResponse {
    std::string token;
    Usuario* user;
};

struct CourseStats {
    float ratioAprobados;
    float ratioAlcance;
};

class Almacenamiento {
    public:
        Almacenamiento(Almacenamiento &other) = delete; // Evita clonar
        void operator=(const Almacenamiento &) = delete; // Evita asignar
        
        static Almacenamiento* getInstancia();

        // CURSOS
        void inscribirEnCurso(int idcurso, const std::string& dniusuario, const std::string& token);
        void desinscribirEnCurso(int idcurso, const std::string& dniusuario, const std::string& token);
        std::vector<Curso> obtenerTodosCursos();
        Curso obtenerCurso(int idcurso);
        CourseStats getCourseStats(int idcurso);
        void eliminarCurso(int idcurso, const std::string& token);
        void editarCurso(int idcurso, const std::string& nombre, const std::string& contenido, const std::string& fechaInicio, const std::string& fechaFin, const std::string& ponente, const std::string& token);
        void crearCurso(const std::string& nombre, const std::string& contenido, const std::string& fechaInicio, const std::string& fechaFin, const std::string& ponente, const std::string& token);
        
        std::vector<Recurso> obtenerTodosRecursos();
        std::vector<Recurso> obtenerRecursosCurso(int idcurso);
        void asignarRecurso(int idcurso, int idrecurso, const std::string& token);
        void desasignarRecurso(int idcurso, const std::string& token);
        void crearRecurso(const std::string& aula, int capacidad, const std::string& token);
        void editarRecurso(int idrecurso, const std::string& aula, int capacidad, const std::string& token);
        void eliminarRecurso(int idrecurso, const std::string& token);

        // USUARIOS
        std::vector<Usuario> obtenerTodosUsuarios();
        Usuario obtenerUsuario(const std::string& dni);
        LoginResponse login(const std::string& username, const std::string& password);
        void logout(const std::string& token);
        LoginResponse registrarUsuario(const std::string& username, const std::string &password, const std::string& dni);
        void anadirUsuario(const std::string& username, const std::string &password, const std::string& dni, const std::string& token);
        void eliminarUsuario(const std::string& dni, const std::string& token);
        void editarUsuario(const std::string& dni, const std::string& nombre, const std::string& contrasena, const std::string& token);

    private:
        std::string getHTTP(std::string url, long& httpStatus);
        std::string postHTTP(std::string url, std::string json, long& httpStatus);

        const std::string BASE_URL = "darkbird.duckdns.org:3333";

    protected:
        Almacenamiento() {}
};


static Almacenamiento* instancia;

#endif