

#pragma once

#include <string>

struct Consola {
    ObjectManager *objectManager;
    Shader *shader;

    Consola(ObjectManager *objManager);
    ~Consola();

    void setShader(Shader *sh);
    void make(std::string func);

};