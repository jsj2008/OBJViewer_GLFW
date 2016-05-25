#include "Textura.hpp"
#include "stringHelper.hpp"
#include "BMPloader.hpp"
#include <sstream>

Textura::Textura():id(0),ruta("") {
}

Textura::Textura(std::string ruta):id(0),ruta(ruta) {
}

Textura::~Textura() {
}

void Textura::cargarTex() {
    id = loadBMP_custom(ruta, GL_NEAREST_MIPMAP_NEAREST);
}

void Textura::cargarTex(int tecnica) {
    id = loadBMP_custom(ruta,tecnica);
}

void Textura::borrarTex() {
    glDeleteTextures(1, &(id));
}

void Textura::activarTex(unsigned int tipo) {
    glActiveTexture(GL_TEXTURE0 + tipo);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Textura::desactivarTex() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Textura::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; i++) {
        tab << "\t";
    }
    ss << tab.str() << "Texture Data" << "\n";
    ss << tab.str() << "\tId = " << id << "\n";
    ss << tab.str() << "\tRuta = " << ruta << "\n";
    return ss.str();
}
