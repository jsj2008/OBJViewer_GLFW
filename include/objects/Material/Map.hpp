
#pragma once

#include <libs/include/glm/glm/vec4.hpp>
#include <libs/include/glm/glm/vec3.hpp>
#include <include/objects/Material/Textures/Textura.hpp>

struct Map{
    float amount;
    glm::vec3 color;
    Textura *textura;
    bool useTexture;

    Map();
    Map(glm::vec3 v);
    Map(Textura *t);

    float getAmount();
    glm::vec3 getColor();
    bool getUseTexture();

    void setAmount(float v);
    void setColor(glm::vec3 v);
    void setTexture(Textura *tex);
    void setUseTexture(bool use);


};