#ifndef PANTALLA_HPP
#define PANTALLA_HPP

class Programa;
class Usuario;

class Pantalla {

    public:
        virtual void recibirTecla(char c) {}
        virtual void renderizar() {}

    protected:
        Programa* programa;
        Usuario* usuario;

};

#endif