//

#include "RenderObject.hpp"
#include "ObjectDataloader.hpp"
#include "Object.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <libs/include/glm/glm/gtx/transform.hpp>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <include/utils/stringHelper.hpp>

RenderObject::RenderObject() :
        vao(0),
        numV(0),
        mode(GL_TRIANGLES),
        modelMatrixAttrib(0) {
}

RenderObject::~RenderObject() {
}

void RenderObject::createVao() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(0);
};

void RenderObject::createBindBuffer(GLuint idShader, const GLchar *name, GLenum tipo,
                                    int elemTipo, int numTotalElem, const void *vector) {
    GLuint auxBuffer;
    GLint auxAttrib;
    auxAttrib = glGetAttribLocation(idShader, name);
    if (auxAttrib < 0) {
        std::cout << "Shader did not contain the '" << name << "' attribute." << std::endl;
    } else {
        glGenBuffers(1, &auxBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, auxBuffer);
        {
            //TODO: Cambiar por glNamedBufferData?? O eliminar glBindBuffer???
            glBufferData(GL_ARRAY_BUFFER, sizeof(tipo) * elemTipo * numTotalElem,
                         vector, GL_STATIC_DRAW);
            glEnableVertexAttribArray((GLuint) auxAttrib);
            glVertexAttribPointer((GLuint) auxAttrib, elemTipo, tipo, GL_FALSE, 0, 0);
        }
    }
}

void RenderObject::loadDataBuffers(GLuint idShader, ObjectData *objectData) {
    glBindVertexArray(vao);
    {
        for (unsigned int i = 0; i < objectData->numBuffers(); i++) {
            DataBuffer *data = objectData->getBuffer(i);
            if (data != NULL) {
                createBindBuffer(idShader, data->name.c_str(), GL_FLOAT, data->groupTipo, data->nElem, data->buffer);
                if (data->name == "in_position")
                    numV = data->nElem;
            }
        }
    }
    glBindVertexArray(0);
}

void RenderObject::setTextureAttrib(GLuint idShader, unsigned int numTex) {
    GLint tLocation0 = glGetUniformLocation(idShader, "myTextures[0]");
    for (unsigned int b = 0; b < numTex; b++) {
        glUniform1i(tLocation0 + b, b);
    }
}

void RenderObject::getUnifLocModelMatrix(GLuint idShader) {
    modelMatrixAttrib = (GLuint) glGetUniformLocation(idShader, "model");
    if (modelMatrixAttrib < 0) {
        std::cout << "Shader did not contain the 'model' uniform." << std::endl;
    }
}

void RenderObject::loadModelUniform() {
    glUniformMatrix4fv(modelMatrixAttrib, 1, GL_FALSE, value_ptr(modelMatrix));
}

void RenderObject::actualizarModelMatrix(Object *basicData) {
    modelMatrix =
            glm::scale(glm::mat4(1.0f), basicData->scale) * translate(glm::mat4(1.0f), basicData->pos) *
            glm::rotate(basicData->rot.w, glm::vec3(basicData->rot)) *
            translate(glm::mat4(1.0f), basicData->center);
}

std::string RenderObject::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    ss << tab.str() << "Render Object Info" << "\n";
    ss << tab.str() << "\tVao = " << vao << "\n";
    ss << tab.str() << "\tNumV = " << numV << "\n";
    ss << tab.str() << "\tMode = " << mode << "\n";
    ss << tab.str() << "\tModelMatrix = \n" << mat4ToString(modelMatrix, tabLevel + 1) << "\n";
    ss << tab.str() << "\tModelMatrixAttrib = " << modelMatrixAttrib << "\n";
    return ss.str();
}





