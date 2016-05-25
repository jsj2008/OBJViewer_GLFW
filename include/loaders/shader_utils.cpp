//
// Created by Javier on 29/10/2015.
//

#include "shader_utils.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Create a NULL-terminated string by reading the provided file
char* readShaderSource(const char* shaderFile) {
    FILE *filePointer;
    char *content = NULL;
    int sizeFile = 0;
    if (shaderFile != NULL) {
        filePointer = fopen(shaderFile, "r");
        if (filePointer != NULL) {
            fseek(filePointer, 0, SEEK_END);
            sizeFile = ftell(filePointer);
            rewind(filePointer);
            if (sizeFile > 0) {
                content = (char *) malloc(sizeof(char) * (sizeFile + 1));
                sizeFile = fread(content, sizeof(char), sizeFile, filePointer);
                content[sizeFile] = '\0';
            }
            fclose(filePointer);
        } else {
            std::cout << "No se encuentra el archivo " << shaderFile << "\n";
        }
    }
    else {
        std::cout << "Ruta del shader vacia\n";
    }
    return content;
}

// Create a GLSL program object from vertex and fragment shader files
GLuint InitShader(const char* vShaderFile, const char* fShaderFile,
                  const char* outputAttributeName) {
    struct Shader {
        const char* filename;
        GLenum type;
        GLchar* source;
    } shaders[2] = { { vShaderFile, GL_VERTEX_SHADER, NULL }, { fShaderFile,
                                    GL_FRAGMENT_SHADER, NULL } };

    GLuint program = glCreateProgram();

    for (int i = 0; i < 2; ++i) {
        Shader &s = shaders[i];
        shaders[i].source = readShaderSource(s.filename);
        if (shaders[i].source == NULL) {
            std::cerr << "Failed to read " << shaders[i].filename << std::endl;
            exit( EXIT_FAILURE);
        }
        GLuint shader = glCreateShader(shaders[i].type);
        glShaderSource(shader, 1, (const GLchar**) &shaders[i].source, NULL);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            std::cerr << s.filename << " failed to compile:" << std::endl;
            GLint logSize;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
            char* logMsg = new char[logSize];
            glGetShaderInfoLog(shader, logSize, NULL, logMsg);
            std::cerr << logMsg << std::endl;
            delete[] logMsg;
            exit( EXIT_FAILURE);
        }

        delete[] s.source;
        glAttachShader(program, shader);
    }
    /* Link output */
    glBindFragDataLocation(program, 0, outputAttributeName);

    /* link  and error check */
    glLinkProgram(program);

    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        printf("Shader program failed to link");
        GLint logSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetProgramInfoLog(program, logSize, NULL, logMsg);
        printf("%s", logMsg);
        delete[] logMsg;
        exit( EXIT_FAILURE);
    }

    /* use program object */
    glUseProgram(program);

    return program;
}