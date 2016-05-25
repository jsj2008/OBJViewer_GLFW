#include "glew.h"
#include "freeglut.h"
#include "InitHelper.hpp"
#include "Raton.hpp"
#include "Teclado.hpp"
#include "BasicObjects.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Object3D.hpp"
#include <iostream>
#include <libs/include/glm/glm/glm.hpp>
#include <include/utils/stringHelper.hpp>
#include <include/loaders/ObjectDataloader.hpp>
#include "LuzPuntual.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

Raton raton(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
Teclado teclado;

Camera *cam;
LuzPuntual *luz;
Object3D *obj;
Shader *shader;

void entradas(float timeDif) {
    if (raton.getCapturePointer()) {
        glutWarpPointer(cam->width / 2, cam->height / 2);
    }
    if (teclado.getKey('k')) {
        raton.toggleCapturePointer();
        teclado.setKey('k', false);
    }
    if (teclado.getKey('e')) {
        glutLeaveMainLoop();
    }
    if (teclado.getKey('f')) {
        glutFullScreenToggle();
        teclado.setKey('f', false);
    }
    if (teclado.getKey('r')) {
        cam->reset();
    }
    if (teclado.getKey('m')) {
        if (obj->renderObj->mode == GL_TRIANGLES) {
            obj->renderObj->mode = GL_LINE_STRIP;
        } else {
            obj->renderObj->mode = GL_TRIANGLES;
        }
        teclado.setKey('m', false);
    }
    if (teclado.getKey('c')) {
        std::cout << cam->toString(0);
    }
    float a = 0, b = 0, c = 0;
    if (teclado.getKey('w')) {
        a = 1;
    }
    if (teclado.getKey('s')) {
        a = -1;
    }
    if (teclado.getKey('a')) {
        b = 1;
    }
    if (teclado.getKey('d')) {
        b = -1;
    }
    if (teclado.getKey('z')) {
        c = 1;
    }
    if (teclado.getKey('x')) {
        c = -1;
    }
    if (teclado.getKey('1')) {
        luz->position = cam->pos;
    }
//    if (teclado.getKey('2')) {
//        obj->data = plane();
//        obj->inicializarObjeto(shader->id);
//    }
//    if (teclado.getKey('3')) {
//        obj->data = cube();
//        obj->inicializarObjeto(shader->id);
//    }
//    if (teclado.getKey('4')) {
//        obj->data = axis();
//        obj->inicializarObjeto(shader->id);
//        obj->renderObj->mode = GL_LINES;
//    }
//    if (teclado.getKey('5')) {
//        obj->data = circle(50);
//        obj->inicializarObjeto(shader->id);
//    }
//    if (teclado.getKey('6')) {
//        obj->data = pyramid();
//        obj->inicializarObjeto(shader->id);
//    }
    cam->moveFPS(a + raton.wheel * 5, b, c, timeDif);
    raton.resetWheel();
    if (raton.getCapturePointer()) {
        cam->rotateFoco(raton.getCenterPointerX(cam->width),
                        raton.getCenterPointerY(cam->height),
                        timeDif * 10);
    }
}

void onMouse(int x, int y) {
    raton.setPointer(x, y);
}

void onWheel(int wheel, int dir, int x, int y) {
    raton.setWheel(wheel, dir, x, y);
}

void onButtons(int button, int state, int x, int y) {
//    switch (button) {
//        case GLUT_LEFT_BUTTON:
//            if (state == GLUT_DOWN)
//                raton.setButtons(true, false, false);
//            else
//                raton.setButtons(false, false, false);
//            break;
//        case GLUT_RIGHT_BUTTON:
//            if (state == GLUT_DOWN)
//                raton.setButtons(false, true, false);
//            else
//                raton.setButtons(false, false, false);
//            break;
//        case GLUT_MIDDLE_BUTTON:
//            if (state == GLUT_DOWN)
//                raton.setButtons(false, false, true);
//            else
//                raton.setButtons(false, false, false);
//            break;
//    }
}

void key_down_func(unsigned char key, int x, int y) {
    teclado.setKey(key, true);
}

void key_up_func(unsigned char key, int x, int y) {
    teclado.setKey(key, false);
}

void reshape(int w, int h) {
    cam->setWidth(w);
    cam->setHeight(h);
    raton.setPointer(w / 2, h / 2);
    glViewport(0, 0, w, h);
}

void animate() {
    glutPostRedisplay();
}

void visible(int vis) {
    if (vis == GLUT_VISIBLE)
        glutIdleFunc(animate);
    else
        glutIdleFunc(0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    entradas(0.0005f);
    glUseProgram(shader->id);
    cam->loadCamAttrib();
    luz->loadLuzAttrib();
    obj->material->activateTextures();
    obj->renderObj->actualizarModelMatrix(&obj->basicData);
    obj->renderObj->loadModelUniform();
    glBindVertexArray(obj->renderObj->vao);
    glDrawArrays(obj->renderObj->mode, 0, obj->renderObj->numV);
    glBindVertexArray(0);
    glutSwapBuffers();
}

void initObjects() {
    shader = new Shader("basic");
    shader->loadShader();
    std::cout << "Shader Cargado" << std::endl;

    cam = new Camera;
    cam->linkCamAttrib(shader->id);
    luz = new LuzPuntual;
    luz->linkLuzAttrib(shader->id);
    std::cout << "Cam & Light atributes cargados" << std::endl;

    obj = new Object3D(1);
    obj->basicData.pos = glm::vec3(0, 5, 0);
    obj->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
//    obj->data = loadObjectData("C:\\Users\\Javier\\ClionProjects\\MotorGrafico_0_5\\data\\troll\\troll_raw.obj");
    obj->data = loadObjectData2("prueba1.raw");
//    obj->data = new ObjectData;
//    cube(obj->data);
    obj->inicializarObjeto(shader->id);
    obj->material->ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    obj->material->diffuseColor = glm::vec4(0.6f, 0.0f, 0.0f, 0.0f);
    obj->material->specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    obj->material->glossinessColor = glm::vec4(100.0f, 0.0f, 0.0f, 0.0f);
    obj->material->selfIluminatedColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    obj->material->alphaColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    obj->material->bumpColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
    obj->material->reflectionColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    obj->material->refractionColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    obj->material->loadUnifMaterial();
    std::cout << obj->toString(0);
    std::cout << "Objetos inicializados" << std::endl;

}

void init(int argc, char *argv[]) {
    init_Glut_Glew(argc, argv);
    inicializarConsola();
    initFuncionGLs();
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(onMouse);
    glutMouseWheelFunc(onWheel);
    glutMouseFunc(onButtons);
    glutKeyboardFunc(key_down_func);
    glutKeyboardUpFunc(key_up_func);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutVisibilityFunc(visible);
    glutIdleFunc(animate);
    glutDisplayFunc(display);
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

}

int main(int argc, char *argv[]) {
    //std::cout << "Cargando Objeto" << std::endl;
    //ObjectData *objectData = loadObjectData("C:\\Users\\Javier\\ClionProjects\\MotorGrafico_0_5\\data\\troll\\troll_raw.obj");
//    for (int i = 0; i < 100; ++i) {
//        std::cout << vec3ToString(((glm::vec3*)objectData->buffers[0].buffer)[i]) << "\n";
//    }







//    ObjectData *objectData = new ObjectData;
//    glm::vec3 buffer[3] = {glm::vec3(1,1,1),glm::vec3(2,2,2),glm::vec3(3,3,3)};
//    objectData->addBuffer("PrimerBuffer",3,sizeof(float),3,buffer);

//    std::cout << "Cargando Objeto Viejo" << std::endl;
//    ObjectData *objectData = loadObjectData("C:\\Users\\Javier\\Documents\\GitHub\\MotorGrafico\\data\\troll\\troll_raw.obj");
//    std::cout << objectData->toString(0) << std::endl;
//
//    std::cout << "Guardando Objeto Nuevo" << std::endl;
//    saveObjectData2("prueba1.raw",objectData);

//    std::cout << "Cargando Objeto Nuevo" << std::endl;
//    ObjectData *objectData2 = loadObjectData2("prueba1.raw");
//    std::cout << objectData2->toString(0) << std::endl;







//    for (int i = 0; i < 100; ++i) {
//        std::cout << vec3ToString(((glm::vec3*)objectData2->buffers[0].buffer)[0]) << "\n";
//    }
//    saveObjectData("C:\\Users\\Javier\\ClionProjects\\MotorGrafico_0_5\\data\\troll\\troll_rawCopia3.obj",objectData);

    std::cout << "Abriendo Motor Grafico" << std::endl;
    init(argc, argv);
    std::cout << "Motor Grafico abierto" << std::endl;
    initObjects();
    std::cout << "Abriendo juego" << std::endl;
    glutMainLoop();
    return 0;
}
