
#pragma once

//#include <glew.h>
#include <string>
#include <libs/lib/glew.h>

//#define DiffuseIndex 0
//#define NormalIndex 1
//#define SpecularIndex 2
//#define GlossIndex 3
//#define AlphaIndex 4
//#define SelfLIndex 5

/*
    0 diffuseTex;
    1 specularTex;
    2 glossinessTex;
    3 selfIluminatedTex;
    4 alphaTex;
    5 bumpTex;
    6 reflectionTex;
    7 refractionTex;
 */

//enum tTipo {Diffuse, Normal, Specular, Glossiness, Alpha, SelfLight};

struct Textura{

    GLuint id;
    std::string ruta;

    Textura();
    Textura(std::string ruta);
    ~Textura();

    void cargarTex();
    void cargarTex(int tecnica);
    void borrarTex();

    void activarTex(unsigned int tipo);
    void desactivarTex();

    std::string toString(int tabLevel);

};
