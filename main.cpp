#include "libs/lib/glew.h"
#include "libs/lib/glfw3.h"
#include <iostream>
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

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 300;

GLFWwindow *window;

Raton raton(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
Teclado teclado;

Camera *cam;
LuzPuntual *luz;
Object3D *obj;
Shader *shader;

double oldTime;
int nFrame = 0;

void entradas(float timeDif) {

    if (teclado.getKey('f')) {
//        glutFullScreenToggle();
        teclado.setKey('f', false);
    }

    if (teclado.getKey('m')) {
        if (obj->renderObj->mode == GL_TRIANGLES) {
            obj->renderObj->mode = GL_LINE_STRIP;
        } else {
            obj->renderObj->mode = GL_TRIANGLES;
        }
        teclado.setKey('m', false);
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

}

//
//void onMouse(int x, int y) {
//    raton.setPointer(x, y);
//}
//
//void onWheel(int wheel, int dir, int x, int y) {
//    raton.setWheel(wheel, dir, x, y);
//}
//
//void onButtons(int button, int state, int x, int y) {
////    switch (button) {
////        case GLUT_LEFT_BUTTON:
////            if (state == GLUT_DOWN)
////                raton.setButtons(true, false, false);
////            else
////                raton.setButtons(false, false, false);
////            break;
////        case GLUT_RIGHT_BUTTON:
////            if (state == GLUT_DOWN)
////                raton.setButtons(false, true, false);
////            else
////                raton.setButtons(false, false, false);
////            break;
////        case GLUT_MIDDLE_BUTTON:
////            if (state == GLUT_DOWN)
////                raton.setButtons(false, false, true);
////            else
////                raton.setButtons(false, false, false);
////            break;
////    }
//}
//void reshape(int w, int h) {
//    cam->setWidth(w);
//    cam->setHeight(h);
//    raton.setPointer(w / 2, h / 2);
//    glViewport(0, 0, w, h);
//}
//
//void animate() {
//    glutPostRedisplay();
//}
//
//void visible(int vis) {
//    if (vis == GLUT_VISIBLE)
//        glutIdleFunc(animate);
//    else
//        glutIdleFunc(0);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    entradas(0.0005f);
//    glUseProgram(shader->id);
//    cam->loadCamAttrib();
//    luz->loadLuzAttrib();
//    obj->material->activateTextures();
//    obj->renderObj->actualizarModelMatrix(&obj->basicData);
//    obj->renderObj->loadModelUniform();
//    glBindVertexArray(obj->renderObj->vao);
//    glDrawArrays(obj->renderObj->mode, 0, obj->renderObj->numV);
//    glBindVertexArray(0);
//    glutSwapBuffers();
//}
//

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
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        luz->position = cam->pos;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {

        obj->data = new ObjectData;
        cube(obj->data);
    }



    float a = 0, b = 0, c = 0;
    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        a = 1;
    }
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        a = -1;
    }
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        b = 1;
    }
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        b = -1;
    }
    if (key == GLFW_KEY_Z && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        c = 1;
    }
    if (key == GLFW_KEY_X && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        c = -1;
    }
    cam->moveFPS(a + raton.wheel * 5, b, c, 0.0005f);
//    raton.resetWheel();
}

void dropFile(GLFWwindow *window, int n, const char **ss) {
    for (int i = 0; i < n; i++) {
        const char *s = ss[i];
        std::cout << s << std::endl;
    }
}

void reshape(GLFWwindow *window, int sx, int sy) {
    cam->width = sx;
    cam->height = sy;
    glViewport(0, 0, sx, sy);
}

void cursorPos(GLFWwindow *window, double x, double y) {
    raton.setPointer(x, y);
//    std::cout << raton.getCenterPointerX(cam->width) << " " <<
//    raton.getCenterPointerY(cam->height) << std::endl;
}

void fpsCounter() {
    double actualTime = glfwGetTime();
    if (actualTime - oldTime > 1.0f) {
        oldTime = actualTime;
        std::cout << nFrame << " FPS" << std::endl;
        nFrame = 0;
    } else {
        nFrame++;
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
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Title", NULL, NULL);
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

    glfwSetKeyCallback(window, keyRecorder);
    glfwSetDropCallback(window, dropFile);
    glfwSetWindowSizeCallback(window, reshape);
    glfwSetCursorPosCallback(window, cursorPos);


    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(50.0f);
    //glEnable(GL_CULL_FACE);
    glClearColor(0.25f, 0.25f, 0.35f, 0.0f);


    initObjects();

    oldTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        fpsCounter();
        if (raton.getCapturePointer()) {
            glfwSetCursorPos(window, cam->width / 2, cam->height / 2);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader->id);
        cam->loadCamAttrib();
        luz->loadLuzAttrib();
        obj->material->activateTextures();
        obj->renderObj->actualizarModelMatrix(&obj->basicData);
        obj->renderObj->loadModelUniform();
        glBindVertexArray(obj->renderObj->vao);
        glDrawArrays(obj->renderObj->mode, 0, obj->renderObj->numV);
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (raton.getCapturePointer()) {
            cam->rotateFoco(raton.getCenterPointerX(cam->width),
                            raton.getCenterPointerY(cam->height),
                            0.00005f * 10);
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
