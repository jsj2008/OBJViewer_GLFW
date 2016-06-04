
#pragma once

#include "ObjectData.hpp"
#include "Object.hpp"
#include <libs/lib/glew.h>
#include "glm/glm/mat4x4.hpp"

struct RenderObject{
    GLuint vao;
    int numV;
    GLenum mode;
    glm::mat4 modelMatrix;
    GLuint modelMatrixAttrib;

    RenderObject();
    ~RenderObject();

    void createBindBuffer(GLuint idShader, const GLchar *name, GLenum tipo, int elemTipo, int numTotalElem,
                          const void *vector);

    void setTextureAttrib(GLuint idShader, unsigned int numTex);

    void loadDataBuffers(GLuint idShader, ObjectData *objectData);

    void createVao();

    void getUnifLocModelMatrix(GLuint idShader);

    void loadModelUniform();

    std::string toString(int tabLevel);

    void actualizarModelMatrix(Object *basicData);
};