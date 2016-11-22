#include "Material.hpp"
#include "include/utils/stringHelper.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>

//        ambientColor(0.1f, 0.1f, 0.15f, 1.0f),
//        diffuseColor(0.6f, 0.6f, 0.6f, 1.0f),
//        specularColor(0.0f, 0.0f, 0.0f, 1.0f),
//        glossinessColor(30.0f, 0.0f, 0.0f, 1.0f),
//        selfIluminatedColor(0.0f, 0.0f, 0.0f, 1.0f),
//        alphaColor(1.0f, 1.0f, 1.0f, 1.0f),
//        bumpColor(0.0f, 0.0f, 0.0f, 1.0f),
//        reflectionColor(0.0f, 0.0f, 0.0f, 1.0f),
//        refractionColor(0.0f, 0.0f, 0.0f, 1.0f),

Material::Material() :
        id(0),
        name("Material"),
        shaderId(0),
        attribLocationMaps(0),
        attribLocationTex(0) {
    for (int j = 0; j < MAX_TEXTURES; ++j) {
        maps[j] = NULL;
    }
    std::stringstream ss;
    ss << "_" << id;
    name += ss.str();
}

//Material::Material(unsigned int id) :
//        id(id),
//        name("Material"),
//        shaderId(0),
//        attribLocationMat(0),
//        attribLocationTex(0) {
//    std::stringstream ss;
//    ss << "_" << id;
//    name += ss.str();
//    for (int i = 0; i < MAX_TEXTURES; ++i) {
//        textures[i] = NULL;
//    }
//}
//
//Material::Material(const Material &mat) :
//        id(mat.id),
//        name(mat.name),
//        shaderId(mat.shaderId),
//        attribLocationMat(mat.attribLocationMat),
//        attribLocationTex(mat.attribLocationTex) {
//    for (int i = 0; i < MAX_TEXTURES; ++i) {
//        textures[i] = mat.textures[i];
//    }

Material::~Material() {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        if(maps[i] != NULL){
            delete(maps[i]);
        }
    }
}

unsigned int Material::getId() {
    return id;
}

std::string Material::getName() {
    return name;
}

unsigned int Material::getShaderId() {
    return shaderId;
}

Map *Material::getMap(int tipo) {
    return maps[tipo];
}

void Material::setId(unsigned int id) {
    this->id = id;
}

void Material::setName(std::string name) {
    this->name = name;
}

void Material::setShaderId(unsigned int shaderId) {
    this->shaderId = shaderId;
}


void Material::addMap(Map *map, int tipo) {
    maps[tipo] = map;
}

void Material::activateTextures() {
    for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
        if (maps[i] != NULL && maps[i]->useTexture)
            maps[i]->textura->activarTex(i);
    }
}

void Material::loadMaterialFile(std::string ruta) {
    std::cout << "Cargando texturas" << std::endl;
    std::ifstream file(ruta);
    int tipo;
    std::string s;
    while (file >> tipo >> s) {
        addMap(new Map(new Textura(s)), tipo);
        std::cout << "Textura " << tipo << " " << s << " cargada" << std::endl;
    }
    file.close();
}

void Material::getUnifLocMaterial() {
    attribLocationAmount = (GLuint) glGetUniformLocation(shaderId, "amount[0]");
    if (attribLocationAmount < 0) {
        std::cout << "Shader did not contain the 'amount[0]' uniform." << std::endl;
    }
    attribLocationMaps = (GLuint) glGetUniformLocation(shaderId, "material[0]");
    if (attribLocationMaps < 0) {
        std::cout << "Shader did not contain the 'material[0]' uniform." << std::endl;
    }
    attribLocationTex = (GLuint) glGetUniformLocation(shaderId, "myTextures[0]");
    if (attribLocationTex < 0) {
        std::cout << "Shader did not contain the 'myTextures[0]' uniform." << std::endl;
    }
}

void Material::loadUnifMaterial() {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        if(maps[i] != NULL) {
            glUniform1f(attribLocationAmount + i,maps[i]->amount);
            glUniform3fv(attribLocationMaps + i, 1, glm::value_ptr(maps[i]->color));
        }
    }
//    if (attribLocationTex > -1) {
    for (unsigned int b = 0; b < MAX_TEXTURES; b++) {
        glUniform1i(attribLocationTex + b, b);
    }
//    }
}

std::string Material::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    ss << tab.str() << "Material Data" << "\n";
    ss << tab.str() << "\tId = " << id << "\n";
    ss << tab.str() << "\tName = " << name << "\n";
//    ss << tab.str() << "\tAmbientColor = " << vec4ToString(ambientColor) << "\n";
//    ss << tab.str() << "\tDiffuseColor = " << vec4ToString(diffuseColor) << "\n";
//    ss << tab.str() << "\tSpecularColor = " << vec4ToString(specularColor) << "\n";
//    ss << tab.str() << "\tGlossinessColor = " << vec4ToString(glossinessColor) << "\n";
//    ss << tab.str() << "\tSelfIluminatedColor = " << vec4ToString(selfIluminatedColor) << "\n";
//    ss << tab.str() << "\tAlphaColor = " << vec4ToString(alphaColor) << "\n";
//    ss << tab.str() << "\tBumpColor = " << vec4ToString(bumpColor) << "\n";
//    ss << tab.str() << "\tReflectionColor = " << vec4ToString(reflectionColor) << "\n";
//    ss << tab.str() << "\tReflactionColor = " << vec4ToString(refractionColor) << "\n";
    ss << tab.str() << "\tTextures =" << "\n";
    for (int t = 0; t < MAX_TEXTURES; ++t) {
        switch (t) {
            case 0:
                ss << tab.str() << "\t\tDiffuse" << "\n";
                break;
            case 1:
                ss << tab.str() << "\t\tSpecular" << "\n";
                break;
            case 2:
                ss << tab.str() << "\t\tGlossiness" << "\n";
                break;
            case 3:
                ss << tab.str() << "\t\tSelfIluminated" << "\n";
                break;
            case 4:
                ss << tab.str() << "\t\tAlpha" << "\n";
                break;
            case 5:
                ss << tab.str() << "\t\tBump" << "\n";
                break;
            case 6:
                ss << tab.str() << "\t\tReflection" << "\n";
                break;
            case 7:
                ss << tab.str() << "\t\tRefraction" << "\n";
                break;
            default:
                ss << tab.str() << "\t\tUnnamed" << "\n";
                break;
        }
//        ss << tab.str() << ((textures[t] == NULL) ? "\t\t\tNULL\n" : textures[t]->toString(tabLevel + 2));
    }
    return ss.str();
}









