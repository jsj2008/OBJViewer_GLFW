
#pragma once

#include <include/objects/Object3D.hpp>

#define MAX_OBJECT 100

struct ObjectManager {
    //Implementar estructura octotree
    Object3D *objects[MAX_OBJECT];
    int cont;

    ObjectManager();

    void insertObject(Object3D *obj);

    Object3D *getObject(int i);

    Object3D *getLastObject();

    void compact();
};