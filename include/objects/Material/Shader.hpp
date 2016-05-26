//
// Created by Javier on 10/11/2015.
//

#ifndef MOTORGRAFICO_0_3_SHADER_HPP
#define MOTORGRAFICO_0_3_SHADER_HPP

//#include "glew.h"
#include <string>
#include <libs/lib/glew.h>

struct Shader{

    GLuint id;
    std::string name;

    Shader(const std::string &name);
    ~Shader();


    void loadShader();
};

#endif //MOTORGRAFICO_0_3_SHADER_HPP
