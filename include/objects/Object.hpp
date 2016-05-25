
#pragma once

#include "glew.h"
#include "glm/glm/vec3.hpp"
#include "glm/glm/vec4.hpp"
#include <string>
#include <vector>

struct Object {

    unsigned int id;
    unsigned int parentId;
    std::string name;
    glm::vec3 center;
    glm::vec3 pos;
    glm::vec4 rot;
    glm::vec3 scale;

    Object(unsigned int id);

    void setId(unsigned int id);
    void setParentId(unsigned int parentId);
    void setName(std::string name);
    void setCenter(glm::vec3 v);
    void setPos(glm::vec3 v);
    void setRot(glm::vec4 v);
    void setScale(glm::vec3 v);

    unsigned int getId();
    unsigned int getParentId();
    std::string getName();
    glm::vec3 getCenter();
    glm::vec3 getPos();
    glm::vec4 getRot();
    glm::vec3 getScale();

    std::string toString(int tabLevel);

};
