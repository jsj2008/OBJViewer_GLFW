//
// Created by Javier on 06/04/2016.
//

#include <iostream>
#include <include/objects/Object3D.hpp>
#include <include/manager/ObjectManager.hpp>
#include "Consola.hpp"


Consola::Consola(ObjectManager *objManager) {
    objectManager = objManager;
}

Consola::~Consola() {

}

void Consola::make(std::string func) {
    if (func.find("create", 0) != std::string::npos) {
//        int posX = 0;
//        std::cin >> posX;
//        Object3D *obj = new Object3D(1, "prueba1.raw", "data\\troll\\troll_raw.tex");
//        obj->basicData.pos = glm::vec3(posX, 0, 0);
//        obj->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
//        obj->material->diffuseColor.a = 0.0f;
//        obj->setShader(0);
        objectManager->insertObject(new Object3D(1, "prueba1.raw", "data\\troll\\troll_raw.tex"));
        objectManager->getLastObject()->basicData.pos = glm::vec3(objectManager->cont * 100, 0, 0);
        objectManager->getLastObject()->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
//        objectManager->getLastObject()->material->diffuseColor.a = 0.0f;
        objectManager->getLastObject()->setShader(shader->id);
    }
}

void Consola::setShader(Shader *sh) {
    shader = sh;
}





