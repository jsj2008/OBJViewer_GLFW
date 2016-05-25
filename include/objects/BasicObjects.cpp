#include <iostream>
#include <include/utils/stringHelper.hpp>
#include <cstdlib>
#include <cmath>
//#include <cmath>
#include "BasicObjects.hpp"

ObjectData *axis() {
    glm::vec3 vertices[] = {
            glm::vec3(10000, 0, 0),
            glm::vec3(-10000, 0, 0),
            glm::vec3(0, 10000, 0),
            glm::vec3(0, -10000, 0),
            glm::vec3(0, 0, 10000),
            glm::vec3(0, 0, -10000)
    };
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(6, 0, 0, &(vertices[0]), NULL, NULL);
    return data;
}

ObjectData *plane() {
    glm::vec3 vertices[] = {
            glm::vec3(100, 100, 0),
            glm::vec3(-100, 100, 0),
            glm::vec3(-100, -100, 0),
            glm::vec3(-100, -100, 0),
            glm::vec3(100, -100, 0),
            glm::vec3(100, 100, 0)
    };
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(6, 0, 0, &(vertices[0]), NULL, NULL);
    return data;
}

void cube(ObjectData *data) {
    glm::vec3 vertices[36] = {
            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 1.0f, -1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, -1.0f, 1.0)
    };
//    ObjectData *data = new ObjectData;
    data->addBuffer("in_position", 36, sizeof(float), 3, vertices);
//    data->annadirArrayVertices(36, 0, 0, vertices, NULL, NULL);
}

ObjectData *circle(int res) {
//    std::cout << "PasoX" << std::endl;
    glm::vec3 vertices[res * 3];
    glm::vec3 anterior = glm::vec3((float) sin((((float) res*3-3) / (res*3)) * 2 * 3.1415926535f),
                                   (float) cos((((float) res*3-3) / (res*3)) * 2 * 3.1415926535f), 0);
    for (int j = 0; j < res * 3; j += 3) {
        vertices[j] = glm::vec3(0);
        vertices[j + 1] = anterior;
        anterior = vertices[j + 2] = glm::vec3((float) sin((((float) j) / (res*3)) * 2 * 3.1415926535f),
                                               (float) cos((((float) j) / (res*3)) * 2 * 3.1415926535f), 0);
    }
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(res * 3, 0, 0, &(vertices[0]), NULL, NULL);
    return data;
}

ObjectData *sphere(int hRes, int vRes) {
    glm::vec3 vertices[hRes][vRes];
    for (int i = 0; i < vRes; ++i) {
        for (int j = 0; j < hRes; ++j) {
//            vertices[i][j].x = sin(j / hRes);
//            vertices[i][j].y = cos(j / hRes);
            vertices[i][j].z = vRes;
        }
    }
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(36, 0, 0, vertices[25], NULL, NULL);
    return data;
}

ObjectData *geosphere() {
    glm::vec3 vertices[] = {
    };
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(36, 0, 0, vertices, NULL, NULL);
    return data;
}

ObjectData *cylinder() {
    glm::vec3 vertices[] = {
    };
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(36, 0, 0, vertices, NULL, NULL);
    return data;
}

ObjectData *cone() {
    glm::vec3 vertices[] = {
    };
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(36, 0, 0, vertices, NULL, NULL);
    return data;
}

ObjectData *pyramid() {
    glm::vec3 vertices[] = {
            glm::vec3(1, 1, 0),
            glm::vec3(-1, 1, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(-1, -1, 0),
            glm::vec3(1, -1, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(-1, 1, 0),
            glm::vec3(-1, -1, 0),
            glm::vec3(0, 0, 1),
            glm::vec3(1, -1, 0),
            glm::vec3(1, 1, 0),
            glm::vec3(0, 0, 1),
    };
    ObjectData *data = new ObjectData;
//    data->annadirArrayVertices(12, 0, 0, &(vertices[0]), NULL, NULL);
    return data;
}