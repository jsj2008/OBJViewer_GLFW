
#include "Map.hpp"

//TODO: Importar las funciones de carga de texturas (segun el uso)

Map::Map() {
    amount = 0.0f;
    color = glm::vec3(0,0,0);
    textura = NULL;
    useTexture = false;
}

Map::Map(glm::vec3 v) {
    amount = 0.0f;
    color = v;
    textura = NULL;
    useTexture = false;
}

Map::Map(Textura *t) {
    amount = 0.0f;
    color = glm::vec3(0,0,0);
    setTexture(t);
}

float Map::getAmount() {
    return amount;
}

glm::vec3 Map::getColor() {
    return color;
}

void Map::setAmount(float v) {
    amount = v;
}

void Map::setColor(glm::vec3 v) {
    color = v;
}

void Map::setTexture(Textura *tex) {
    textura = tex;
    setUseTexture(true);
}

void Map::setUseTexture(bool use) {
    useTexture = use;
    if(useTexture)
        textura->cargarTex();
    else
        textura->borrarTex();
}

bool Map::getUseTexture() {
    return useTexture;
}
