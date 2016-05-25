/*
 * Object3D.cpp
 *
 *  Created on: 13/2/2015
 *      Author: JAVIER
 */

#include "ObjectData.hpp"
#include "glm/glm/gtx/perpendicular.hpp"
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <include/utils/stringHelper.hpp>
#include <iostream>
#include <include/loaders/ObjectDataloader.hpp>

ObjectData::ObjectData() :
        fileDir("") {
}

ObjectData::ObjectData(std::string fileDir) :
        fileDir(fileDir) {
}

ObjectData::ObjectData(const ObjectData &obj) :
        fileDir(obj.fileDir) {
}

ObjectData::~ObjectData() {
}

unsigned int ObjectData::numBuffers(){
    return buffers.size();
}

DataBuffer *ObjectData::getBuffer(unsigned int i) {
    return (i < buffers.size()) ? &(buffers[i]) : NULL;
}

DataBuffer *ObjectData::getBuffer(std::string name) {
    bool encontrado = false;
    unsigned int i = 0;
    if (buffers.size() > 0) {
        do {
            if (buffers[i].name == name) {
                encontrado = true;
            } else {
                i++;
            }
        } while ((i < buffers.size()) && !encontrado);
    }
    return encontrado ? &(buffers[i]) : NULL;
}

void ObjectData::addBuffer(std::string name, unsigned int nElem, unsigned int sizeTipo, unsigned int groupTipo, void *buffer) {
    bool insertado = false;
    DataBuffer newBuffer = {name, nElem, sizeTipo, groupTipo, NULL};
    newBuffer.buffer = malloc(nElem * sizeTipo * groupTipo);
    memcpy(newBuffer.buffer, buffer, nElem * sizeTipo * groupTipo);
    if (buffers.size() > 0) {
        unsigned int i = 0;
        do {
            if (buffers[i].name == name) {
                buffers.insert(buffers.begin() + i, newBuffer);
                insertado = true;
            }
            i++;
        } while ((i < buffers.size()) && !insertado);
    }
    if (!insertado)
        buffers.push_back(newBuffer);
}

void ObjectData::deleteBuffer(std::string name) {
    bool insertado = false;
    if (buffers.size() > 0) {
        unsigned int i = 0;
        do {
            if (buffers[i].name == name) {
                buffers.erase(buffers.begin() + i);
                insertado = true;
            }
            i++;
        } while ((i < buffers.size()) && !insertado);
    }
}

std::string ObjectData::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    ss << tab.str() << "Vertex Array Info" << "\n";
    for (unsigned int j = 0; j < buffers.size(); ++j) {
        ss << tab.str() << "\tName = " << buffers[j].name << "\n";
        ss << tab.str() << "\t\tN_Elem = " << buffers[j].nElem << "\n";
        ss << tab.str() << "\t\tSizeType = " << buffers[j].sizeTipo << "\n";
        ss << tab.str() << "\t\tGroupType = " << buffers[j].groupTipo << "\n";
        ss << tab.str() << "\t\tBuffer = " << buffers[j].buffer << "\n";
        ss << "\n";
        ss << tab.str() << "\t\tBuffer[0] = " << vec3ToString(((glm::vec3 *) buffers[j].buffer)[0]) << "\n";
        ss << tab.str() << "\t\tBuffer[1] = " << vec3ToString(((glm::vec3 *) buffers[j].buffer)[1]) << "\n";
        ss << tab.str() << "\t\tBuffer[2] = " << vec3ToString(((glm::vec3 *) buffers[j].buffer)[2]) << "\n";
    }
    return ss.str();
}




