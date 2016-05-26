#include "Object3D.hpp"
#include "include/utils/stringHelper.hpp"
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>


Object3D::Object3D(unsigned int id) :
        basicData(id),
        data(NULL),
        material(NULL),
        renderObj(NULL){
}


Object3D::Object3D(const Object3D &obj):
        basicData(obj.basicData),
        data(NULL),
        material(obj.material),
        renderObj(obj.renderObj)
{
}


std::string Object3D::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    ss << tab.str() << "Object3D Data" << "\n";
    ss << tab.str() << basicData.toString(1) << "\n";
    ss << tab.str() << ((data == NULL) ? "\tObjectData = NULL" : data->toString(1)) << "\n";
    ss << tab.str() << ((material == NULL) ? "\tMaterial = NULL" : material->toString(1)) << "\n";
    ss << tab.str() << ((renderObj == NULL) ? "\tRender = NULL" : renderObj->toString(1)) << "\n";
    return ss.str();
}

void Object3D::inicializarObjeto(unsigned int shaderId) {
//    if(data->numN == 0)
//        data->calcNormals();
//    if(data->numT == 0)
//        data->calcTexCoord();
    material = new Material(0);
    material->setShaderId(shaderId);
    material->getUnifLocMaterial(shaderId);
    material->loadUnifMaterial();
    material->loadTexFile("data\\troll\\troll_raw.tex");
    material->loadTextures();
    renderObj = new RenderObject();
    renderObj->createVao();
    renderObj->getUnifLocModelMatrix(shaderId);
    renderObj->actualizarModelMatrix(&basicData);
    renderObj->loadModelUniform();
    renderObj->loadDataBuffers(shaderId, data);
}

bool Object3D::loadOnFile() {
    FILE *archivo;
    std::string fileName;
    archivo = fopen(fileName.c_str(), "rb");
    if (archivo != NULL) {
        fread(&basicData, sizeof(int), 1, archivo);
        fread(&data, sizeof(int), 1, archivo);
        fread(&material, sizeof(int), 1, archivo);
        fread(&renderObj, sizeof(int), 1, archivo);
        return true;
    }
    return false;
}

bool Object3D::saveOnFile() {
    FILE *archivo;
    std::string fileName;
//    fileName.append();
    archivo = fopen(fileName.c_str(), "wb");
    if (archivo != NULL) {
        fwrite(&basicData, sizeof(int), 1, archivo);
//        fwrite(&modelMatrix, sizeof(int), 1, archivo);
        fwrite(&data, sizeof(int), 1, archivo);
        fwrite(&material, sizeof(int), 1, archivo);
//        fwrite(&vao, sizeof(int), 1, archivo);
//        fwrite(&modelAttrib, sizeof(int), 1, archivo);
    } else {
        return false;
    }
    return true;
}





