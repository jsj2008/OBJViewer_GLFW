/*
 * ObjectDataloader.cpp
 *
 *  Created on: 20/7/2015
 *      Author: Javier
 */

#include "ObjectDataloader.hpp"
#include "glm/glm/vec3.hpp"
#include "glm/glm/vec2.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <include/utils/stringHelper.hpp>

struct preObject {
    int numV, numT, numN;
    glm::vec3 *vertices;
    glm::vec2 *texturas;
    glm::vec3 *normales;

    preObject() :
            numV(0), numT(0), numN(0),
            vertices(NULL),
            texturas(NULL),
            normales(NULL) {
    }
};

ObjectData *loadObjectData(std::string ruta) {
    ObjectData *objeto = new ObjectData;
    preObject preObj;
    FILE *archivoRaw;
    archivoRaw = fopen(ruta.c_str(), "rb");
    if (archivoRaw != NULL) {
        fread(&preObj.numV, sizeof(int), 1, archivoRaw);
        fread(&preObj.numT, sizeof(int), 1, archivoRaw);
        fread(&preObj.numN, sizeof(int), 1, archivoRaw);
        if (preObj.numV > 0)
            preObj.vertices = (glm::vec3 *) malloc(sizeof(glm::vec3) * preObj.numV);
        if (preObj.numT > 0)
            preObj.texturas = (glm::vec2 *) malloc(sizeof(glm::vec2) * preObj.numT);
        if (preObj.numN > 0)
            preObj.normales = (glm::vec3 *) malloc(sizeof(glm::vec3) * preObj.numN);
        if (preObj.numV > 0)
            fread(preObj.vertices, sizeof(glm::vec3), preObj.numV, archivoRaw);
        if (preObj.numT > 0)
            fread(preObj.texturas, sizeof(glm::vec2), preObj.numT, archivoRaw);
        if (preObj.numN > 0)
            fread(preObj.normales, sizeof(glm::vec3), preObj.numN, archivoRaw);
        objeto->addBuffer("in_position", (unsigned int) preObj.numV, sizeof(float), 3, preObj.vertices);
        objeto->addBuffer("in_texCoord", (unsigned int) preObj.numT, sizeof(float), 2, preObj.texturas);
        objeto->addBuffer("in_normal", (unsigned int) preObj.numN, sizeof(float), 3, preObj.normales);
        fclose(archivoRaw);
    } else {
        std::cout << "Archivo " << ruta << " no encontrado" << std::endl;
    }
    return objeto;
}

//void saveObjectData(char *ruta, ObjectData obj) {
//    FILE *archivoRaw;
//    archivoRaw = fopen(ruta, "wb");
//    int numV = obj.getNumV();
//    int numT = obj.getNumT();
//    int numN = obj.getNumN();
//    fwrite(&numV, sizeof(int), 1, archivoRaw);
//    fwrite(&numT, sizeof(int), 1, archivoRaw);
//    fwrite(&numN, sizeof(int), 1, archivoRaw);
//    if (obj.getVertices() != NULL)
//        fwrite(obj.getVertices(), sizeof(glm::vec3), obj.getNumV(), archivoRaw);
//    if (obj.getTextureCoords() != NULL)
//        fwrite(obj.getTextureCoords(), sizeof(glm::vec2), obj.getNumT(), archivoRaw);
//    if (obj.getNormales() != NULL)
//        fwrite(obj.getNormales(), sizeof(glm::vec3), obj.getNumN(), archivoRaw);
//    fclose(archivoRaw);
//}

ObjectData *loadObjectData2(std::string ruta) {
    std::fstream file(ruta, std::fstream::in | std::fstream::binary);
    ObjectData *obj = new ObjectData;
    if (file.is_open()) {
        file.seekg(0, file.end);
        long long int eof = file.tellg();
        file.seekg(0, file.beg);
        do {
//            std::cout << "Inicio vuelta " << file.tellg() << std::endl;
            DataBuffer *data = new DataBuffer;
            file >> data->name;
            file >> data->nElem;
            file >> data->sizeTipo;
            file >> data->groupTipo;
            file.seekg(1, file.cur); // Guarrada????
            data->buffer = calloc(data->nElem, data->sizeTipo * data->groupTipo);
            file.read((char *) data->buffer, data->sizeTipo * data->nElem * data->groupTipo);
            obj->addBuffer(data->name, data->nElem, data->sizeTipo, data->groupTipo, data->buffer);
//            std::cout << "Fin vuelta " << file.tellg() << std::endl;
        } while (file.tellg() != eof);
        file.close();
    }
    return obj;
}

void saveObjectData2(std::string ruta, ObjectData *obj) {
    std::fstream file(ruta, std::fstream::out | std::fstream::binary);
    if (file.is_open()) {
        for (unsigned int i = 0; i < obj->numBuffers(); i++) {
            DataBuffer *data = obj->getBuffer(i);
            file << data->name << std::endl;
            file << data->nElem << std::endl;
            file << data->sizeTipo << std::endl;
            file << data->groupTipo << std::endl;
            file.write((const char *) data->buffer, data->sizeTipo * data->nElem * data->groupTipo);
        }
        file.close();
    }
}


//    FILE *archivoRaw = fopen(ruta.c_str(), "rb");
//    std::cout << "A la carga" << std::endl;
//    if (archivoRaw != NULL) {
//        while (!feof(archivoRaw)) {
//            DataBuffer data;
//            size_t s;
//            fread(&s, sizeof(size_t), 1, archivoRaw);
//            std::cout << "S = " << s;
//            char *name = new char[s + 1];
//            std::cout << "Name1 = " << name[0];
//            fread(name, s, 1, archivoRaw);
//            std::cout << "Name2 = " << name[0];
//            name[s] = '\0';
//            fread(&(data.nElem), sizeof(unsigned int), 1, archivoRaw);
//            std::cout << "Data NElem = " << data.nElem << std::endl;
//            fread(&(data.sizeTipo), sizeof(unsigned int), 1, archivoRaw);
//            std::cout << "Data Size = " << data.sizeTipo << std::endl;
//            fread(&(data.groupTipo), sizeof(unsigned int), 1, archivoRaw);
//            std::cout << "Data Group = " << data.groupTipo << std::endl;
//            data.buffer = malloc(data.nElem * data.sizeTipo);
//            fread(data.buffer, data.sizeTipo, data.nElem, archivoRaw);
//            std::cout << "Data Buffer = " << data.nElem << std::endl;
//            obj->addBuffer("Holaa", data.nElem, data.sizeTipo, data.groupTipo, data.buffer);
//            std::cout << "Cargado N" << std::endl;
//        }
//    }
//    fclose(archivoRaw);
//    return obj;
//}

//void saveObjectData(std::string ruta, ObjectData *obj) {
//    FILE *archivoRaw = fopen(ruta.c_str(), "wb");
//    if (archivoRaw != NULL) {
//        for (unsigned int i = 0; i < obj->numBuffers(); ++i) {
//            DataBuffer *data = obj->getBuffer(i);
//            size_t s = data->name.size();
//            const char *name = data->name.c_str();
//            fwrite(&(s), sizeof(size_t), 1, archivoRaw);
//            fwrite(&(*name), s, 1, archivoRaw);
//            fwrite(&(data->nElem), sizeof(unsigned int), 1, archivoRaw);
//            fwrite(&data->sizeTipo, sizeof(unsigned int), 1, archivoRaw);
//            fwrite(&data->groupTipo, sizeof(unsigned int), 1, archivoRaw);
//            fwrite(&(((float *) data->buffer)[0]), data->sizeTipo, data->nElem, archivoRaw);
//        }
//    }
//    fclose(archivoRaw);
//}




















