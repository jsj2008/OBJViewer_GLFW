#include "libs/lib/glew.h"
#include "libs/lib/glfw3.h"
#include <iostream>
#include <cstdio>
#include "InitHelper.hpp"
#include "Raton.hpp"
#include "Teclado.hpp"
#include "BasicObjects.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "Object3D.hpp"
#include "glm/glm/glm.hpp"
#include "stringHelper.hpp"
#include "ObjectDataloader.hpp"
#include "LuzPuntual.hpp"

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 600;
bool fullscreen = false;

const int N_OBJ = 2;

GLFWwindow *window;

Raton raton;
Teclado teclado;

Camera *cam;
LuzPuntual *luz;
Object3D *obj[N_OBJ];
Shader *shader;

double oldTime, lastFrameTime;
int nFrame = 0;

void entradas(double timeDif) {
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
    cam->setWidth(WINDOW_WIDTH);
    cam->setHeight(WINDOW_HEIGHT);
    cam->linkCamAttrib(shader->id);
    luz = new LuzPuntual;
    luz->linkLuzAttrib(shader->id);
    std::cout << "Cam & Light atributes cargados" << std::endl;
    for (int i = 0; i < N_OBJ; i++) {
        obj[i] = new Object3D(1, "prueba1.raw", "data\\troll\\troll_raw.tex");
        obj[i]->basicData.pos = glm::vec3(i*100, 0, 0);
        obj[i]->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
        obj[i]->material->diffuseColor.a = 0.0f;
        obj[i]->setShader(shader->id);
    }

//    std::cout << obj[0]->toString(0);
    std::cout << "Objetos inicializados" << std::endl;
}

void dropFile(GLFWwindow *window, int n, const char **ss) {
    for (int i = 0; i < n; i++) {
        const char *s = ss[i];
        std::cout << s << std::endl;
        obj[1] = new Object3D(2);
        obj[1]->basicData.pos = glm::vec3(5, 0, 0);
        obj[1]->basicData.scale = glm::vec3(0.1f, 0.1f, 0.1f);
        obj[1]->data = loadObjectData2(s);
        obj[1]->inicializarObjeto(shader->id);
        obj[1]->material->ambientColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        obj[1]->material->diffuseColor = glm::vec4(0.6f, 0.0f, 0.0f, 0.0f);
        obj[1]->material->specularColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        obj[1]->material->glossinessColor = glm::vec4(100.0f, 0.0f, 0.0f, 0.0f);
        obj[1]->material->selfIluminatedColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
        obj[1]->material->alphaColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        obj[1]->material->bumpColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        obj[1]->material->reflectionColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        obj[1]->material->refractionColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        obj[1]->material->loadUnifMaterial();
        std::cout << obj[1]->toString(0);
    }
}

void reshape(GLFWwindow *window, int sx, int sy) {
    cam->width = sx;
    cam->height = sy;
    glViewport(0, 0, sx, sy);
}

void cursorPos(GLFWwindow *window, double x, double y) {
    raton.setPointer(x,y);
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
//        std::cout << nFrame << " FPS" << std::endl;
        glfwSetWindowTitle(window,ss.c_str());
        nFrame = 0;
    } else {
        nFrame++;
    }
}

void keyRecorder(GLFWwindow *window, int key, int scancode, int action, int mods) {
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
    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        GLFWmonitor *monitor = NULL;
        if(!fullscreen) {
            monitor = glfwGetPrimaryMonitor();
            WINDOW_WIDTH = glfwGetVideoMode(monitor)->width;
            WINDOW_HEIGHT = glfwGetVideoMode(monitor)->height;
            fullscreen = true;
        } else {
            WINDOW_WIDTH = 500;
            WINDOW_HEIGHT = 500;
            fullscreen = false;
        }
        glfwDestroyWindow(window);
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sivax Extreme Engine", monitor, NULL);
        if (!window) {
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cout << "glewInit failed, aborting." << std::endl;
        }

        glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        glfwSetKeyCallback(window, keyRecorder);
        glfwSetDropCallback(window, dropFile);
        glfwSetWindowSizeCallback(window, reshape);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glPointSize(50.0f);
        glEnable(GL_CULL_FACE);
        glClearColor(0.25f, 0.25f, 0.35f, 0.0f);
        initObjects();
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        luz->position = cam->pos;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        obj[0]->data = new ObjectData;
        cube(obj[0]->data);
        obj[0]->renderObj->loadDataBuffers(shader->id, obj[0]->data);
    }
}

int main(int argc, char *argv[]) {
    std::cout << "Abriendo Motor Grafico" << std::endl;
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = NULL;
    if(fullscreen) {
        monitor = glfwGetPrimaryMonitor();
        WINDOW_WIDTH = glfwGetVideoMode(monitor)->width;
        WINDOW_HEIGHT = glfwGetVideoMode(monitor)->height;
    }
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sivax Extreme Engine", monitor, NULL);
    if (!window) {
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "glewInit failed, aborting." << std::endl;
    }
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, keyRecorder);
    glfwSetDropCallback(window, dropFile);
    glfwSetWindowSizeCallback(window, reshape);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(50.0f);
    glEnable(GL_CULL_FACE);
    glClearColor(0.25f, 0.25f, 0.35f, 0.0f);

    initObjects();

    lastFrameTime = oldTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double actualTime = glfwGetTime();
        double difTime = actualTime - oldTime;
        oldTime = actualTime;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        raton.setPointer(xpos,ypos);
        entradas(difTime);
        fpsCounter();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader->id);
        cam->loadCamAttrib();
        luz->loadLuzAttrib();
        for (int i = 0; i < N_OBJ; i++) {
            if (obj[i] != NULL) {
                obj[i]->refreshData();
                glBindVertexArray(obj[i]->renderObj->vao);
                glDrawArrays(obj[i]->renderObj->mode, 0, obj[i]->renderObj->numV);
            }
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
