
#pragma once

#include "Textura.hpp"
#include "Shader.hpp"
#include "glm/glm/vec4.hpp"
#include <string>
#include <vector>

/*
    0 diffuseTex;
    1 specularTex;
    2 glossinessTex;
    3 selfIluminatedTex;
    4 alphaTex;
    5 bumpTex; NormalTex?
    6 reflectionTex;
    7 refractionTex;
 */

//TODO: Revisar rango texturas

const int MAX_TEXTURES = 8;

struct Material{
    unsigned int id;
    std::string name;
    unsigned int shaderId;

    glm::vec4 ambientColor;
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;
    glm::vec4 glossinessColor;
    glm::vec4 selfIluminatedColor;
    glm::vec4 alphaColor;
    glm::vec4 bumpColor;
    glm::vec4 reflectionColor;
    glm::vec4 refractionColor;

    Textura *textures[MAX_TEXTURES];

    GLuint attribLocationMat;
    GLuint attribLocationTex;

    Material();
    Material(unsigned int id);
    Material(const Material &mat);
    ~Material();

    unsigned int getId();
    std::string getName();
    unsigned int getShaderId();
    glm::vec4 getAmbient();
    glm::vec4 getDiffuseColor();
    glm::vec4 getSpecularColor();
    glm::vec4 getGlossinessColor();
    glm::vec4 getSelfIluminatedColor();
    glm::vec4 getAlphaColor();
    glm::vec4 getBumpColor();
    glm::vec4 getReflectionColor();
    glm::vec4 getRefractionColor();
    Textura *getTexture(int tipo);
    Textura *getTextures();

    void setId(unsigned int id);
    void setName(std::string name);
    void setShaderId(unsigned int shaderId);
    void setAmbient(glm::vec4 ambient);
    void setDiffuseColor(glm::vec4 diffuseColor);
    void setSpecularColor(glm::vec4 specularColor);
    void setGlossinessColor(glm::vec4 glossinessColor);
    void setSelfIluminatedColor(glm::vec4 selfIluminatedColor);
    void setAlphaColor(glm::vec4 alphaColor);
    void setBumpColor(glm::vec4 bumpColor);
    void setReflectionColor(glm::vec4 reflectionColor);
    void setRefractionColor(glm::vec4 refractionColor);
    void setTextures(Textura *textures[]);
    void addTexture(Textura *texture,int tipo);

    void loadTexFile(std::string ruta);

    void loadTextures();
    void activateTextures();

    void getUnifLocMaterial();
    void loadUnifMaterial();

    std::string toString(int tabLevel);
};
