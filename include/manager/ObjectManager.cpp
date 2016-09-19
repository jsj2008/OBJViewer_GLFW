
#include "ObjectManager.hpp"

ObjectManager::ObjectManager() {
    for (int i = 0; i < MAX_OBJECT; i++) {
        objects[i] = NULL;
    }
    cont = 0;
}

void ObjectManager::insertObject(Object3D *obj) {
    if (cont < MAX_OBJECT) {
        objects[cont] = obj;
        cont++;
    }
}

Object3D *ObjectManager::getObject(int i) {
    return objects[i];
}

Object3D *ObjectManager::getLastObject() {
    return objects[cont - 1];
}

void ObjectManager::compact() {
    //TODO: Compactar la memoria
}

