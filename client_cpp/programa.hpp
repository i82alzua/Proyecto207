#ifndef PROGRAMA_HPP
#define PROGRAMA_HPP

#include "UI/pantalla.hpp"
#include "UI/enumPantallas.hpp"

#include "DTO/usuario.hpp"

class Programa {

public:
    Programa();

    void init();
    void quit();
    void cambiarPantalla(TIPO_PANTALLA pantalla, void* arg = NULL);
    std::string getSessionToken();
    void setSessionToken(const std::string& token);
    Usuario* getUsuario();
    void setUsuario(Usuario* usuario);

private:
    Pantalla* pantallaActual;
    Usuario* usuario;
    std::string sessionToken;

    bool running;

};

#endif