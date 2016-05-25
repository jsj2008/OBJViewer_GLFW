
#include "stringHelper.hpp"
#include <sstream>

std::string vec2ToString(glm::vec2 v) {
    std::stringstream ss;
    ss << "[" << v.x << " " << v.y << " " << "]";
    return ss.str();
}

std::string vec3ToString(glm::vec3 v) {
    std::stringstream ss;
    ss << "[" << v.x << " " << v.y << " " << v.z << "]";
    return ss.str();
}

std::string vec4ToString(glm::vec4 v) {
    std::stringstream ss;
    ss << "[" << v.x << " " << v.y << " " << v.z << " " << v.w << "]";
    return ss.str();
}

std::string mat4ToString(glm::mat4 m, int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    for (int i = 0; i < m.length(); ++i) {
        ss << tab.str() <<  "[ ";
        for (int j = 0; j < m.length(); ++j) {
            ss << m[i][j] << " ";
        }
        ss << " ]" << "\n";
    }
    return ss.str();
}

