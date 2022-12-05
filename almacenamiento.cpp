#include "almacenamiento.hpp"

Almacenamiento* Almacenamiento::getInstancia() {
    if (instancia == nullptr) {
        instancia = new Almacenamiento();
    }

    return instancia;
}

//TODO
Almacenamiento::añadirCurso(Curso* curso) {



}

//TODO
Almacenamiento::eliminarCurso() {



}

//TODO
Almacenamiento::modificarCurso() {



}

//TODO
Almacenamiento::añadirUsuario(Usuario* usuario) {



}

//TODO
Almacenamiento::eliminarUsuario() {



}

//TODO
Almacenamiento::modificarUsuario() {



}

Almacenamiento::void getCursoFromDataBase() {


}

Almacenamiento::void getUsuarioFromDataBase() {


}

std::vector<Curso> Almacenamiento::obtenerTodosCursos() {

    return std::vector<Curso> {
        Curso(0, "asdgsdag", {"","asdf"}, "asdfsadf", "asdfdsaf"),
        Curso(1, "holi", {"","asdf"}, "asdfsadf", "asdfdsaf"),
        Curso(2, "hola", {"","asdf"}, "asdfsadf", "asdfdsaf"),
    };
    
}

