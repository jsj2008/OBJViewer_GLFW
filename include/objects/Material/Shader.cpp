//
// Created by Javier on 10/11/2015.
//

#include "Shader.hpp"
#include "shader_utils.hpp"
#include <sstream>
#include <iostream>


Shader::Shader(const std::string &name) : id(0), name(name) {

}

Shader::~Shader() {
}

//TODO: Quitar ruta fija
void Shader::loadShader(){
    std::stringstream ssV;
    std::stringstream ssF;
    ssV << "data\\Shaders\\";
    ssF << "data\\Shaders\\";
    ssV << name;
    ssF << name;
    ssV << "Shader.vert";
    ssF << "Shader.frag";
    //id = InitShader(ssV.str().c_str(),ssF.str().c_str(),name.c_str());
    id = InitShader("data\\Shaders\\basicShader.vert",
                    "data\\Shaders\\basicShader.frag",
                    name.c_str());
}

