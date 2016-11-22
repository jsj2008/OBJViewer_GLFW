
#pragma once

#include "Textura.hpp"
#include "Shader.hpp"
#include "glm/glm/vec4.hpp"
#include "Map.hpp"
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

/*
#define AMBIENT 8
#define DIFFUSE 0
#define SPECULAR 1
#define GLOSSINESS 2
#define SELFILUMINATED 3
#define ALPHA 4
#define BUMP 5
#define REFLECTION 6
#define REFRACTION 7
 */

//TODO: Revisar rango texturas

const int MAX_TEXTURES = 8;

struct Material {
    unsigned int id;
    std::string name;
    unsigned int shaderId;

    Map *maps[MAX_TEXTURES];

    GLuint attribLocationAmount;
    GLuint attribLocationMaps;
    GLuint attribLocationTex;

    Material();

    ~Material();

    unsigned int getId();
    std::string getName();
    unsigned int getShaderId();
    Map *getMap(int tipo);

    void setId(unsigned int id);
    void setName(std::string name);
    void setShaderId(unsigned int shaderId);
    void addMap(Map *map, int tipo);

    void loadMaterialFile(std::string ruta);
    void activateTextures();

    void getUnifLocMaterial();
    void loadUnifMaterial();

    std::string toString(int tabLevel);
};
