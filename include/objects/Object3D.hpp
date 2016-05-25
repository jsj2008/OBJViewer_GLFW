
#pragma once

#include "Object.hpp"
#include "ObjectData.hpp"
#include "Material.hpp"
#include "renderObject.hpp"
#include "glm/glm/mat4x4.hpp"
#include "glew.h"
#include <string>

struct Object3D {

    Object basicData;
    ObjectData *data;
    Material *material;
    renderObject *renderObj;

    Object3D(unsigned int id);
    Object3D(const Object3D &obj);

    void inicializarObjeto(unsigned int shaderId);

    std::string toString(int tabLevel);

    bool saveOnFile();
    bool loadOnFile();




};
