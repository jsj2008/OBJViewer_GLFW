#include "Material.hpp"
#include "include/utils/stringHelper.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>


//TODO: Convert in a array
Material::Material() :
        id(0),
        name("Material"),
        shaderId(0),
        ambientColor(0.1f, 0.1f, 0.15f, 1.0f),
        diffuseColor(0.6f, 0.6f, 0.6f, 1.0f),
        specularColor(0.0f, 0.0f, 0.0f, 1.0f),
        glossinessColor(30.0f, 0.0f, 0.0f, 1.0f),
        selfIluminatedColor(0.0f, 0.0f, 0.0f, 1.0f),
        alphaColor(1.0f, 1.0f, 1.0f, 1.0f),
        bumpColor(0.0f, 0.0f, 0.0f, 1.0f),
        reflectionColor(0.0f, 0.0f, 0.0f, 1.0f),
        refractionColor(0.0f, 0.0f, 0.0f, 1.0f),
        attribLocationMat(0),
        attribLocationTex(0) {
    std::stringstream ss;
    ss << "_" << id;
    name += ss.str();
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        textures[i] = NULL;
    }
}

Material::Material(unsigned int id) :
        id(id),
        name("Material"),
        shaderId(0),
        ambientColor(0.0f, 0.0f, 0.0f, 1.0f),
        diffuseColor(0.6f, 0.6f, 0.6f, 1.0f),
        specularColor(0.0f, 0.0f, 0.0f, 1.0f),
        glossinessColor(30.0f, 0.0f, 0.0f, 1.0f),
        selfIluminatedColor(0.0f, 0.0f, 0.0f, 1.0f),
        alphaColor(1.0f, 1.0f, 1.0f, 1.0f),
        bumpColor(0.0f, 0.0f, 0.0f, 1.0f),
        reflectionColor(0.0f, 0.0f, 0.0f, 1.0f),
        refractionColor(0.0f, 0.0f, 0.0f, 1.0f),
        attribLocationMat(0),
        attribLocationTex(0) {
    std::stringstream ss;
    ss << "_" << id;
    name += ss.str();
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        textures[i] = NULL;
    }
}

Material::Material(const Material &mat) :
        id(mat.id),
        name(mat.name),
        shaderId(mat.shaderId),
        ambientColor(mat.ambientColor),
        diffuseColor(mat.diffuseColor),
        specularColor(mat.specularColor),
        glossinessColor(mat.glossinessColor),
        selfIluminatedColor(mat.selfIluminatedColor),
        alphaColor(mat.alphaColor),
        bumpColor(mat.bumpColor),
        reflectionColor(mat.reflectionColor),
        refractionColor(mat.refractionColor),
        attribLocationMat(mat.attribLocationMat),
        attribLocationTex(mat.attribLocationTex) {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        textures[i] = mat.textures[i];
    }
}

Material::~Material() {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        if (textures[i] != NULL)
            delete textures[i];
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

glm::vec4 Material::getAmbient() {
    return ambientColor;
}

glm::vec4 Material::getDiffuseColor() {
    return diffuseColor;
}

glm::vec4 Material::getSpecularColor() {
    return specularColor;
}

glm::vec4 Material::getGlossinessColor() {
    return glossinessColor;
}

glm::vec4 Material::getSelfIluminatedColor() {
    return selfIluminatedColor;
}

glm::vec4 Material::getAlphaColor() {
    return alphaColor;
}

glm::vec4 Material::getBumpColor() {
    return bumpColor;
}

glm::vec4 Material::getReflectionColor() {
    return reflectionColor;
}

glm::vec4 Material::getRefractionColor() {
    return refractionColor;
}

Textura *Material::getTexture(int tipo) {
    return textures[tipo];
}

Textura *Material::getTextures() {
    return textures[0];
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

void Material::setAmbient(glm::vec4 ambient) {
    this->ambientColor = ambient;
}

void Material::setDiffuseColor(glm::vec4 diffuseColor) {
    this->diffuseColor = diffuseColor;
}

void Material::setSpecularColor(glm::vec4 specularColor) {
    this->specularColor = specularColor;
}

void Material::setGlossinessColor(glm::vec4 glossinessColor) {
    this->glossinessColor = glossinessColor;
}

void Material::setSelfIluminatedColor(glm::vec4 selfIluminatedColor) {
    this->selfIluminatedColor = selfIluminatedColor;
}

void Material::setAlphaColor(glm::vec4 alphaColor) {
    this->alphaColor = alphaColor;
}

void Material::setBumpColor(glm::vec4 bumpColor) {
    this->bumpColor = bumpColor;
}

void Material::setReflectionColor(glm::vec4 reflectionColor) {
    this->reflectionColor = reflectionColor;
}

void Material::setRefractionColor(glm::vec4 refractionColor) {
    this->refractionColor = refractionColor;
}

void Material::setTextures(Textura *textures[MAX_TEXTURES]) {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        this->textures[i] = textures[i];
    }
}

void Material::addTexture(Textura *texture, int tipo) {
    this->textures[tipo] = texture;
}

void Material::loadTextures() {
    for (int i = 0; i < MAX_TEXTURES; ++i) {
        if (textures[i] != NULL)
            textures[i]->cargarTex();
    }
}


void Material::activateTextures() {
    for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
        if (textures[i] != NULL)
            textures[i]->activarTex(i);
    }
}

void Material::loadTexFile(std::string ruta) {
    std::cout << "Cargando texturas" << std::endl;
    std::ifstream file(ruta);
    int tipo;
    std::string s;
    while (file >> tipo >> s) {
        addTexture(new Textura(s), tipo);
        std::cout << "Textura " << tipo << " " << s << " cargada" << std::endl;
    }
    file.close();
}

void  Material::getUnifLocMaterial() {
    attribLocationMat = (GLuint) glGetUniformLocation(shaderId, "material[0]");
    if (attribLocationMat < 0) {
        std::cout << "Shader did not contain the 'material[0]' uniform." << std::endl;
    }
    attribLocationTex = (GLuint) glGetUniformLocation(shaderId, "myTextures[0]");
    if (attribLocationTex < 0) {
        std::cout << "Shader did not contain the 'myTextures[0]' uniform." << std::endl;
    }
}

void  Material::loadUnifMaterial() {
    glm::vec4 material[] = {
            ambientColor,
            diffuseColor,
            specularColor,
            glossinessColor,
            selfIluminatedColor,
            alphaColor,
            bumpColor,
            reflectionColor,
            refractionColor
    };
//    if (attribLocationMat > -1) {
        for (int i = 0; i < MAX_TEXTURES; ++i) {
            glUniform4fv(attribLocationMat + i, 1, glm::value_ptr(material[i]));
        }
//    }
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
    ss << tab.str() << "\tAmbientColor = " << vec4ToString(ambientColor) << "\n";
    ss << tab.str() << "\tDiffuseColor = " << vec4ToString(diffuseColor) << "\n";
    ss << tab.str() << "\tSpecularColor = " << vec4ToString(specularColor) << "\n";
    ss << tab.str() << "\tGlossinessColor = " << vec4ToString(glossinessColor) << "\n";
    ss << tab.str() << "\tSelfIluminatedColor = " << vec4ToString(selfIluminatedColor) << "\n";
    ss << tab.str() << "\tAlphaColor = " << vec4ToString(alphaColor) << "\n";
    ss << tab.str() << "\tBumpColor = " << vec4ToString(bumpColor) << "\n";
    ss << tab.str() << "\tReflectionColor = " << vec4ToString(reflectionColor) << "\n";
    ss << tab.str() << "\tReflactionColor = " << vec4ToString(refractionColor) << "\n";
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
        ss << tab.str() << ((textures[t] == NULL) ? "\t\t\tNULL\n" : textures[t]->toString(tabLevel + 2));
    }
    return ss.str();
}







