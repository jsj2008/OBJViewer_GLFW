#include <iostream>
#include <cstdio>
#include <afxres.h>
#include "InitHelper.hpp"
#include "Raton.hpp"
#include "Teclado.hpp"
#include "BasicObjects.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Object3D.hpp"
#include "manager/ObjectManager.hpp"
#include "Consola.hpp"
#include "glm/glm/glm.hpp"
#include "stringHelper.hpp"
#include "ObjectDataloader.hpp"
#include "LuzPuntual.hpp"

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;
int actual_width = 600;
int actual_height = 600;
bool fullscreen = false;

GLFWwindow *window;

ObjectManager objManager;

Raton raton;
Teclado teclado;
Consola consola(&objManager);

Camera *cam;
LuzPuntual *luz;
Shader *shader;

double oldTime, lastFrameTime;
int nFrame = 0;

void entradas(double timeDif) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    raton.setPointer(xpos, ypos);
    glfwSetCursorPos(window,actual_width/2,actual_height/2);
    raton.setPointer(actual_width/2,actual_height/2);

    float a, b, c, CAM_VEL;
    CAM_VEL = 0.1f;
    a = b = c = 0;

    if (glfwGetKey(window, GLFW_KEY_W)) {
        a = CAM_VEL;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        a = -CAM_VEL;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        b = CAM_VEL;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        b = -CAM_VEL;
    }
    if (glfwGetKey(window, GLFW_KEY_Z)) {
        c = CAM_VEL;
    }
    if (glfwGetKey(window, GLFW_KEY_X)) {
        c = -CAM_VEL;
    }
    cam->moveFPS(a + raton.wheel * 5, b, c, timeDif);
    if (raton.getCapturePointer()) {
        cam->rotateFoco(raton.getVelPointerX(),
                        raton.getVelPointerY(),
                        timeDif);
    }

//    if (teclado.getKey('1')) {
//        luz->position = cam->pos;
//    }
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

}

void initObjects() {
    shader = new Shader("basic");
    shader->loadShader();
    std::cout << "Shader Cargado" << std::endl;

    cam = new Camera;
    cam->setWidth(actual_width);
    cam->setHeight(actual_height);
    cam->linkCamAttrib(shader->id);
    luz = new LuzPuntual;
    luz->linkLuzAttrib(shader->id);
    std::cout << "Cam & Light atributes cargados" << std::endl;

    consola.setShader(shader);

    objManager.insertObject(new Object3D(1, "prueba1.raw", "data\\troll\\troll_raw.tex"));
//    objManager.getLastObject()->basicData.pos = glm::vec3(0, 0, 0);
    objManager.getLastObject()->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
    objManager.getLastObject()->material->getMap(0)->color.r = 1.0f;
    objManager.getLastObject()->setShader(shader->id);
    std::cout << "Objetos inicializados" << std::endl;
}

void dropFile(GLFWwindow *window, int n, const char **ss) {
//    for (int i = 0; i < n; i++) {
    objManager.insertObject(new Object3D(1, "prueba1.raw", "data\\troll\\troll_raw.tex"));
    objManager.getLastObject()->basicData.pos = glm::vec3(objManager.cont * 100, 0, 0);
    objManager.getLastObject()->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
//    objManager.getLastObject()->material->diffuseColor.a = 0.0f;
    objManager.getLastObject()->setShader(shader->id);
//}
}

void reshape(GLFWwindow *window, int sx, int sy) {
    cam->width = sx;
    cam->height = sy;
    glViewport(0, 0, sx, sy);
}

//void cursorPos(GLFWwindow *window, double x, double y) {
//    raton.setPointer(x, y);
//    glfwSetCursorPos(window,actual_width/2,actual_height/2);
//}

void keyRecorder(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //TODO: Unir entradas() y keyRecorder()
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        raton.toggleCapturePointer();
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        std::cout << cam->toString(0);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        cam->reset();
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
//        readConsole();
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        fullscreen = !fullscreen;
        GLFWmonitor *monitor = NULL;
        int width = WINDOW_WIDTH;
        int height = WINDOW_HEIGHT;
        if (fullscreen) {
            monitor = glfwGetPrimaryMonitor();
            width = glfwGetVideoMode(monitor)->width;
            height = glfwGetVideoMode(monitor)->height;
        }
        actual_width = width;
        actual_height = height;
        glfwSetWindowMonitor(window, monitor, 100, 100, actual_width, actual_height, 60);
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        luz->position = cam->pos;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
//        obj[0]->data = new ObjectData;
//        cube(obj[0]->data);
//        obj[0]->renderObj->loadDataBuffers(shader->id, obj[0]->data);
    }
}

void fpsCounter() {
    double actualTime = glfwGetTime();
    if (actualTime - lastFrameTime > 1.0f) {
        lastFrameTime = actualTime;
        char fps[5];
        snprintf(fps, 5, "%d", nFrame);
        std::string ss = "Sivax Extreme Engine";
        ss.append(" | FPS: ");
        ss.append(fps);
        glfwSetWindowTitle(window, ss.c_str());
        nFrame = 0;
    } else {
        nFrame++;
    }
}

void readConsole() {
    std::string line;
    std::cin >> line;
    consola.make(line);
}

double deltaTime() {
    double actualTime = glfwGetTime();
    double difTime = actualTime - oldTime;
    oldTime = actualTime;
    return difTime;
}

int main(int argc, char *argv[]) {
    //FreeConsole();  //Deja de mostrar la consola por pantalla
    init_GLFW(&window, 600, 600, false);

    glfwSetKeyCallback(window, keyRecorder);
    glfwSetDropCallback(window, dropFile);
    glfwSetWindowSizeCallback(window, reshape);

    initObjects();

    lastFrameTime = oldTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        entradas(deltaTime());
        fpsCounter();
        glUseProgram(shader->id);
        cam->loadCamAttrib();
        luz->loadLuzAttrib();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i = 0; i < objManager.cont; i++) {
            if (objManager.getObject(i) != NULL) {
                objManager.getObject(i)->refreshData();
                glBindVertexArray(objManager.getObject(i)->renderObj->vao);
                glDrawArrays(objManager.getObject(i)->renderObj->mode, 0, objManager.getObject(i)->renderObj->numV);
            }
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
