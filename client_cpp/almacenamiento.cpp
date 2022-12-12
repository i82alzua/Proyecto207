#include "almacenamiento.hpp"

#include <curl/curl.h>
#include <iostream>

#include "vendor/nlohmann/json.hpp"

using json = nlohmann::json;

Almacenamiento* Almacenamiento::getInstancia() {
    if (instancia == nullptr) {
        instancia = new Almacenamiento();
    }

    return instancia;
}

//-------------------------------------------------------------------//
//                                                                   //
//                            API CURSOS                             //
//                                                                   //
//-------------------------------------------------------------------//


void Almacenamiento::inscribirEnCurso(int idcurso, const std::string& dniusuario, const std::string& token) {
    long http;
    json enrollData = {
        {"courseid", idcurso},
        {"dni", dniusuario},
        {"token", token}
    };

    std::string response = postHTTP("/courses/enroll", enrollData.dump(), http);
    json enrollResponse = json::parse(response);

    std::cout << enrollResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::desinscribirEnCurso(int idcurso, const std::string& dniusuario, const std::string& token) {
    long http;
    json unenrollData = {
        {"courseid", idcurso},
        {"dni", dniusuario},
        {"token", token}
    };

    std::string response = postHTTP("/courses/unenroll", unenrollData.dump(), http);
    json enrollResponse = json::parse(response);

    std::cout << enrollResponse["message"].get<std::string>() << std::endl;
}

std::vector<Curso> Almacenamiento::obtenerTodosCursos() {
    long http;
    std::string response = getHTTP("/courses", http);

    std::vector<Curso> cursos;

    auto json = json::parse(response);
    for (json::iterator it = json.begin(); it != json.end(); ++it) {
        int id;
        std::string nombre;
        std::string content;
        std::string startDate;
        std::string finishDate;
        std::vector<std::string> matriculados;
        
        for (json::iterator courseIt = it->begin(); courseIt != it->end(); ++courseIt) {
            if (courseIt.key() == "nombre") {
                nombre = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "id") {
                id = (*courseIt).get<int>();
            }
            else if (courseIt.key() == "content") {
                content = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "startDate") {
                startDate = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "finishDate") {
                finishDate = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "matriculados") {
                for (json::iterator matriculadosIt = courseIt->begin(); matriculadosIt != courseIt->end(); ++matriculadosIt) {
                    for (json::iterator mtIt = matriculadosIt->begin(); mtIt != matriculadosIt->end(); ++mtIt) {
                        matriculados.push_back((*mtIt).get<std::string>());
                    }
                }
            }
        }

        Curso c(nombre, id, content, matriculados, startDate, finishDate);
        cursos.push_back(c);

    }


    return cursos;

}

Curso Almacenamiento::obtenerCurso(int idcurso) {
    long http;
    json params = {
        {"courseid", idcurso}
    };
    std::string response = postHTTP("/course", params.dump(), http);

    
    std::vector<Curso> cursos;

    auto json = json::parse(response);
    for (json::iterator it = json.begin(); it != json.end(); ++it) {
        int id;
        std::string nombre;
        std::string content;
        std::string startDate;
        std::string finishDate;
        std::vector<std::string> matriculados;
        std::string ponente;
        
        for (json::iterator courseIt = it->begin(); courseIt != it->end(); ++courseIt) {
            if (courseIt.key() == "nombre") {
                nombre = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "id") {
                id = (*courseIt).get<int>();
            }
            else if (courseIt.key() == "content") {
                content = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "startDate") {
                startDate = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "finishDate") {
                finishDate = (*courseIt).get<std::string>();
            }
            else if (courseIt.key() == "matriculados") {
                for (json::iterator matriculadosIt = courseIt->begin(); matriculadosIt != courseIt->end(); ++matriculadosIt) {
                    for (json::iterator mtIt = matriculadosIt->begin(); mtIt != matriculadosIt->end(); ++mtIt) {
                        matriculados.push_back((*mtIt).get<std::string>());
                    }
                }
            }
            else if (courseIt.key() == "ponente") {
                ponente = (*courseIt).get<std::string>();
            }
        }

        Curso c(nombre, id, content, matriculados, startDate, finishDate, ponente);
        cursos.push_back(c);

    }

    return cursos[0];
}

CourseStats Almacenamiento::getCourseStats(int idcurso) {
long http;
    json params = {
        {"courseid", idcurso}
    };
    std::string response = postHTTP("/course/stats", params.dump(), http);

    float passRate;
    float reachRate;

    auto json = json::parse(response);
    for (json::iterator it = json.begin(); it != json.end(); ++it) {
        if (it.key() == "passRate") {
            passRate = atof((*it).get<std::string>().c_str());
        }
        else if (it.key() == "reachRate") {
            reachRate = atof((*it).get<std::string>().c_str());
        }
    }

    return {passRate, reachRate};
}

std::vector<Recurso> Almacenamiento::obtenerTodosRecursos() {
    long http;
    std::string response = getHTTP("/resources", http);

    std::vector<Recurso> resources;
    
    auto json = json::parse(response);
    for (json::iterator arrIt = json.begin(); arrIt != json.end(); ++arrIt) {
        int id;
        std::string aula;
        int capacidad;        
        
        for (json::iterator it = arrIt->begin(); it != arrIt->end(); ++it) {
            if (it.key() == "id") {
                id = (*it).get<int>();
            }
            if (it.key() == "classroom") {
                aula = (*it).get<std::string>();
            }
            else if (it.key() == "capacity") {
                capacidad = (*it).get<int>();
            }
        }

        resources.emplace_back(id, aula, capacidad);
    }

    return resources;
    
}

std::vector<Recurso> Almacenamiento::obtenerRecursosCurso(int idcurso) {
    long http;
    json params = {
        {"courseid", idcurso}
    };
    std::string response = postHTTP("/course/resources", params.dump(), http);

    std::vector<Recurso> resources;
    
    auto json = json::parse(response);
    for (json::iterator arrIt = json.begin(); arrIt != json.end(); ++arrIt) {
        int id;
        std::string aula;
        int capacidad;        
        
        for (json::iterator it = arrIt->begin(); it != arrIt->end(); ++it) {
            if (it.key() == "id") {
                id = (*it).get<int>();
            }
            if (it.key() == "classroom") {
                aula = (*it).get<std::string>();
            }
            else if (it.key() == "capacity") {
                capacidad = (*it).get<int>();
            }
        }

        resources.emplace_back(id, aula, capacidad);
    }

    return resources;
    
}

void Almacenamiento::eliminarCurso(int idcurso, const std::string& token) {
    long http;
    json deleteData = {
        {"courseid", idcurso},
        {"token", token}
    };

    std::string response = postHTTP("/courses/delete", deleteData.dump(), http);
    json deleteResponse = json::parse(response);

    std::cout << deleteResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::editarCurso(int idcurso, const std::string& nombre, const std::string& contenido, const std::string& fechaInicio, const std::string& fechaFin, const std::string& ponente, const std::string& token) {
    long http;
    json editData = {
        {"courseid", idcurso},
        {"token", token},
        {"nombre", nombre},
        {"contenido", contenido},
        {"fechaInicio", fechaInicio},
        {"fechaFin", fechaFin},
        {"ponente", ponente}
    };

    std::string response = postHTTP("/courses/edit", editData.dump(), http);
    json editResponse = json::parse(response);

    std::cout << editResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::crearCurso(const std::string& nombre, const std::string& contenido, const std::string& fechaInicio, const std::string& fechaFin, const std::string& ponente, const std::string& token) {
    long http;
    json createData = {
        {"token", token},
        {"nombre", nombre},
        {"contenido", contenido},
        {"fechaInicio", fechaInicio},
        {"fechaFin", fechaFin},
        {"ponente", ponente}
    };

    std::string response = postHTTP("/courses/add", createData.dump(), http);
    json createResponse = json::parse(response);

    std::cout << createResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::asignarRecurso(int idcurso, int idrecurso, const std::string& token) {
    long http;
    json assignData = {
        {"courseid", idcurso},
        {"resourceid", idrecurso},
        {"token", token}
    };

    std::string response = postHTTP("/courses/resources/add", assignData.dump(), http);
    json assignResponse = json::parse(response);

    std::cout << assignResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::desasignarRecurso(int idcurso, const std::string& token) {
    long http;
    json deleteData = {
        {"courseid", idcurso},
        {"token", token}
    };

    std::string response = postHTTP("/courses/resources/delete", deleteData.dump(), http);
    json deleteResponse = json::parse(response);

    std::cout << deleteResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::crearRecurso(const std::string& aula, int capacidad, const std::string& token) {
    long http;
    json insertData = {
        {"aula", aula},
        {"capacidad", capacidad},
        {"token", token}
    };

    std::string response = postHTTP("/resources/add", insertData.dump(), http);
    json insertResponse = json::parse(response);

    std::cout << insertResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::editarRecurso(int idrecurso, const std::string& aula, int capacidad, const std::string& token) {
    long http;
    json editData = {
        {"idrecurso", idrecurso},
        {"aula", aula},
        {"capacidad", capacidad},
        {"token", token}
    };

    std::string response = postHTTP("/resources/edit", editData.dump(), http);
    json editResponse = json::parse(response);

    std::cout << editResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::eliminarRecurso(int idrecurso, const std::string& token) {
    long http;
    json deleteData = {
        {"resourceid", idrecurso},
        {"token", token}
    };

    std::string response = postHTTP("/resources/delete", deleteData.dump(), http);
    json deleteResponse = json::parse(response);

    std::cout << deleteResponse["message"].get<std::string>() << std::endl;
}




//-------------------------------------------------------------------//
//                                                                   //
//                            API USUARIO                            //
//                                                                   //
//-------------------------------------------------------------------//


std::vector<Usuario> Almacenamiento::obtenerTodosUsuarios() {
    long http;
    std::string response = getHTTP("/users", http);

    std::vector<Usuario> users;

    auto json = json::parse(response);

    for (json::iterator it = json.begin(); it != json.end(); ++it) {
        std::string username;
        std::string password = "";
        std::string dni;
        TIPO_USUARIO tipo;
        for (json::iterator userIt = it->begin(); userIt != it->end(); ++userIt) {
            if (userIt.key() == "username") {
                username = (*userIt).get<std::string>();
            }
            else if (userIt.key() == "dni") {
                dni = (*userIt).get<std::string>();
            }
            else if (userIt.key() == "userrange_id") {
                tipo = (*userIt).get<TIPO_USUARIO>();
            }
        }

        Usuario u(username, password, dni, tipo);
        users.push_back(u);

    }

    return users;
}

Usuario Almacenamiento::obtenerUsuario(const std::string& dni) {
    long http;
    json userData = {
        {"dni", dni}
    };
    std::string response = postHTTP("/user", userData.dump(), http);

    std::vector<Usuario> users;

    auto json = json::parse(response);

    std::string usernameResponse;
    std::string passwordResponse = "";
    std::string dniResponse;
    TIPO_USUARIO tipo;
    for (json::iterator it = json.begin(); it != json.end(); ++it) {
        std::string username;
        std::string password = "";
        std::string dni;
        TIPO_USUARIO tipo;
        for (json::iterator userIt = it->begin(); userIt != it->end(); ++userIt) {
            if (userIt.key() == "username") {
                username = (*userIt).get<std::string>();
            }
            else if (userIt.key() == "dni") {
                dni = (*userIt).get<std::string>();
            }
            else if (userIt.key() == "userrange_id") {
                tipo = (*userIt).get<TIPO_USUARIO>();
            }
        }

        Usuario u(username, password, dni, tipo);
        users.push_back(u);

    }

    return users[0];
}

LoginResponse Almacenamiento::login(const std::string& username, const std::string& password) {
    json loginData = {
        {"username", username},
        {"password", password}
    };
    long http = 0;

    std::string usernameResponse;
    std::string passResponse;
    std::string dniResponse;
    TIPO_USUARIO userrangeResponse;
    std::string tokenResponse;

    std::string apiResponse = postHTTP("/login", loginData.dump(), http);
    json loginResponse = json::parse(apiResponse);

    for (json::iterator it = loginResponse.begin(); it != loginResponse.end(); ++it) {
        if (it.key() == "username") {
            usernameResponse = (*it).get<std::string>();
        }
        else if (it.key() == "dni") {
            dniResponse = (*it).get<std::string>();
        }
        else if (it.key() == "userrange") {
            userrangeResponse = (*it).get<TIPO_USUARIO>();
        }
        else if (it.key() == "token") {
            tokenResponse = (*it).get<std::string>();
        }
    }

    Usuario* user = new Usuario(usernameResponse, passResponse, dniResponse, userrangeResponse);
    return LoginResponse { tokenResponse, user };
}

LoginResponse Almacenamiento::registrarUsuario(const std::string& username, const std::string &password, const std::string& dni) {
    json registerData = {
        {"username", username},
        {"password", password},
        {"dni", dni}
    };
    long http = 0;


    std::string usernameResponse;
    std::string passResponse;
    std::string dniResponse;
    TIPO_USUARIO userrangeResponse;
    std::string tokenResponse;

    std::string apiResponse = postHTTP("/register", registerData.dump(), http);
    json registerResponse = json::parse(apiResponse);
    
    for (json::iterator it = registerResponse.begin(); it != registerResponse.end(); ++it) {
        if (it.key() == "username") {
            usernameResponse = (*it).get<std::string>();
        }
        else if (it.key() == "dni") {
            dniResponse = (*it).get<std::string>();
        }
        else if (it.key() == "userrange") {
            userrangeResponse = (*it).get<TIPO_USUARIO>();
        }
        else if (it.key() == "token") {
            tokenResponse = (*it).get<std::string>();
        }
    }


    Usuario* user = new Usuario(usernameResponse, passResponse, dniResponse, userrangeResponse);
    return LoginResponse { tokenResponse, user };

}

void Almacenamiento::anadirUsuario(const std::string& username, const std::string &password, const std::string& dni, const std::string& token) {
    json registerData = {
        {"username", username},
        {"password", password},
        {"dni", dni},
        {"token", token}
    };
    long http = 0;

    std::string response = postHTTP("/register", registerData.dump(), http);
    json addResponse = json::parse(response);

    std::cout << addResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::logout(const std::string& token) {
    long http;
    json logoutData = {
        {"token", token}
    };

    std::string response = postHTTP("/logout", logoutData.dump(), http);
    json logoutResponse = json::parse(response);

    std::cout << logoutResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::eliminarUsuario(const std::string& dni, const std::string& token) {
    long http;
    json deleteData = {
        {"dni", dni},
        {"token", token}
    };

    std::string response = postHTTP("/users/delete", deleteData.dump(), http);
    json deleteResponse = json::parse(response);

    std::cout << deleteResponse["message"].get<std::string>() << std::endl;
}

void Almacenamiento::editarUsuario(const std::string& dni, const std::string& nombre, const std::string& contrasena, const std::string& token) {
    long http;
    json editData = {
        {"dni", dni},
        {"nombre", nombre},
        {"contrasena", contrasena},
        {"token", token}
    };

    std::string response = postHTTP("/users/edit", editData.dump(), http);
    json editResponse = json::parse(response);

    std::cout << editResponse["message"].get<std::string>() << std::endl;
}




//-------------------------------------------------------------------//
//                                                                   //
//                             CURL                                  //
//                                                                   //
//-------------------------------------------------------------------//


size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t newLength = size*nmemb;
    try
    {
        s->append((char*)contents, newLength);
    }
    catch(std::bad_alloc &e)
    {
        //handle memory problem
        return 0;
    }
    return newLength;
}

std::string Almacenamiento::getHTTP(std::string url, long& httpStatus) {
    std::string responseString;
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, (BASE_URL + url).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);
        
        res = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);


        if (res != CURLE_OK) {
            std::cout << "Error en peticion" << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }

    return responseString;
}

std::string Almacenamiento::postHTTP(std::string url, std::string json, long& httpStatus) {
    std::string responseString;
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        
        
        curl_easy_setopt(curl, CURLOPT_URL, (BASE_URL + url).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);
        
        res = curl_easy_perform(curl);

        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (res != CURLE_OK) {
            std::cout << "Error en peticion" << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }

    return responseString;
}

