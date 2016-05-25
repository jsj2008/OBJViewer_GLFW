/*
 * ObjectData.hpp
 *
 *  Created on: 13/2/2015
 *      Author: JAVIER
 *
 */

#pragma once

#include "glm/glm/vec2.hpp"
#include "glm/glm/vec3.hpp"
//#include <vector>
#include <string>
#include <vector>

struct DataBuffer{
    std::string name;
    unsigned int nElem;
    unsigned int sizeTipo;
    unsigned int groupTipo;
    void *buffer;
};

struct ObjectData {
	std::vector<DataBuffer> buffers;
	std::string fileDir;

	ObjectData();
    ObjectData(std::string fileDir);
    ObjectData(const ObjectData &obj);
	virtual ~ObjectData();

    unsigned int numBuffers();

    DataBuffer *getBuffer(unsigned int i);
    DataBuffer *getBuffer(std::string name);

    void addBuffer(std::string name, unsigned int nElem, unsigned int sizeTipo, unsigned int groupTipo, void *buffer);
    void deleteBuffer(std::string name);

    std::string toString(int tabLevel);
};
