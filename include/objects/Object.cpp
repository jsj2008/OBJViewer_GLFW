#include "Object.hpp"
#include "glm/glm/geometric.hpp"
#include "include/utils/stringHelper.hpp"
#include <sstream>

Object::Object(unsigned int id) :
        id(id),
        parentId(0),
        name("unnamed"),
        center(0),
        pos(0),
        rot(1, 0, 0, 0),
        scale(1) {
}

//////////////////// SETTERS ////////////////////
void Object::setId(unsigned int id) {
    this->id = id;
}

void Object::setParentId(unsigned int parentId) {
    this->parentId = parentId;
}

void Object::setCenter(glm::vec3 v) {
    center = v;
}

void Object::setPos(glm::vec3 v) {
    pos = v;
}

void Object::setRot(glm::vec4 v) {
    rot = v;
    glm::normalize(rot);
}

void Object::setScale(glm::vec3 v) {
    scale = v;
}

void Object::setName(std::string n) {
    name = n;
}

//////////////////// GETTERS ////////////////////
unsigned int Object::getId() {
    return id;
}

unsigned int Object::getParentId() {
    return parentId;
}

std::string Object::getName() {
    return name;
}

glm::vec3 Object::getCenter() {
    return center;
}

glm::vec3 Object::getPos() {
    return pos;
}

glm::vec4 Object::getRot() {
    return rot;
}

glm::vec3 Object::getScale() {
    return scale;
}


std::string Object::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    ss << tab.str() << "Object Data" << "\n";
    ss << tab.str() << "\tId = " << id << "\n";
    ss << tab.str() << "\tParentId = " << parentId << "\n";
    ss << tab.str() << "\tName = " << name << "\n";
    ss << tab.str() << "\tCenter = " << vec3ToString(center) << "\n";
    ss << tab.str() << "\tPos = " << vec3ToString(pos) << "\n";
    ss << tab.str() << "\tRot = " << vec4ToString(rot) << "\n";
    ss << tab.str() << "\tScale = " << vec3ToString(scale) << "\n";
    return ss.str();
}



