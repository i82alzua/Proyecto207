#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>
#include "enumUsuarios.hpp"

class Usuario {

    public:

        Usuario();
        Usuario(std::string& usuario, std::string& contrasena, const std::string& dni, TIPO_USUARIO tipo);
        
        void setUsuario(const std::string& usuario);
        std::string getUsuario();
        
        void setContasena(const std::string& contrasena);
        std::string getContrasena();
        
        void setTipo(TIPO_USUARIO tipo);
        int getTipo();

        void setDNI(const std::string& dni);
        std::string getDNI();

    private:
        std::string usuario;
        std::string contrasena;
        std::string dni;
        TIPO_USUARIO tipo;

};

#endif