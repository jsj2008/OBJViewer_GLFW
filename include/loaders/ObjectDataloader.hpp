/*
 * ObjectDataloader.hpp
 *
 *  Created on: 20/7/2015
 *      Author: Javier
 */

#pragma once

#include <string>
#include "ObjectData.hpp"

ObjectData *loadObjectData(std::string ruta);
ObjectData *loadObjectData2(std::string ruta);
void saveObjectData(std::string ruta, ObjectData *obj);
void saveObjectData2(std::string ruta, ObjectData *obj);
