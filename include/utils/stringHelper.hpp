
#pragma once
#include <glm/glm/vec2.hpp>
#include <glm/glm/vec3.hpp>
#include <glm/glm/vec4.hpp>
#include <glm/glm/mat4x4.hpp>
#include <string>

std::string vec2ToString(glm::vec2 v);

std::string vec3ToString(glm::vec3 v);

std::string vec4ToString(glm::vec4 v);

std::string mat4ToString(glm::mat4 m, int tabLevel);

