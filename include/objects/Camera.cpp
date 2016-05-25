/*
 * Camera.cpp
 *
 *  Created on: 8/3/2015
 *      Author: JAVIER
 */

#include "Camera.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "glm/glm/gtc/quaternion.hpp"
#include <stdio.h>
#include <sstream>
#include <include/utils/stringHelper.hpp>

const float PI = 3.141592653589793238462643383279502884197169399375105820974944f;

Camera::Camera() :
        pos(0, 0, 0), eye(0, 1, 0), up(0, 0, 1),
        width(800), height(800),
        FOV(45.0f),
        nearClipPlane(0.005f), farClipPlane(10000.0f),
        camVelocity(500.0f), camSensibility(0.5f),
        projectionAttrib(5),
        viewAttrib(4),
        camEyeAttrib(6),
        camPosAttrib(7) {
}

Camera::Camera(const Camera &cam) :
        pos(cam.pos), eye(normalize(cam.eye)), up(normalize(cam.up)),
        width(cam.width), height(cam.height),
        FOV(cam.FOV),
        nearClipPlane(cam.nearClipPlane), farClipPlane(cam.farClipPlane),
        camVelocity(cam.camVelocity), camSensibility(cam.camSensibility),
        projectionAttrib(cam.projectionAttrib),
        viewAttrib(cam.viewAttrib),
        camEyeAttrib(cam.camEyeAttrib),
        camPosAttrib(cam.camPosAttrib) {
}

Camera::~Camera() {
}

//////////GETTERS////////
glm::vec3 Camera::getPos() {
    return pos;
}

glm::vec3 Camera::getFocus() {
    return eye;
}

glm::vec3 Camera::getPosFocus() {
    return pos + eye;
}

glm::vec3 Camera::getUp() {
    return up;
}

int Camera::getWidth() {
    return width;
}

int Camera::getHeight() {
    return height;
}

float Camera::getFOV() {
    return FOV;
}

float Camera::getNearClipPlane() {
    return nearClipPlane;
}

float Camera::getFarClipPlane() {
    return farClipPlane;
}

float Camera::getCamVelocity() {
    return camVelocity;
}

float Camera::getCamSensibility() {
    return camSensibility;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(pos, pos + eye, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(FOV * PI / 180.0f, 1.0f * width / height, nearClipPlane,
                            farClipPlane);
}

//////////SETTERS////////
void Camera::setPos(glm::vec3 v) {
    pos = v;
}

void Camera::setFocus(glm::vec3 v) {
    eye = normalize(v);
}

void Camera::setUp(glm::vec3 v) {
    up = normalize(v);
}

void Camera::setWidth(int w) {
    width = w;
}

void Camera::setHeight(int h) {
    height = h;
}

void Camera::setFOV(float fov) {
    FOV = fov;
}

void Camera::setNearClipPlane(float nearClip) {
    nearClipPlane = nearClip;
}

void Camera::setFarClipPlane(float farClip) {
    farClipPlane = farClip;
}

void Camera::setCamVelocity(float camVel) {
    camVelocity = camVel;
}

void Camera::setCamSensibility(float camSens) {
    camSensibility = camSens;
}

void Camera::reset() {
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
    eye = glm::vec3(0.0f, 1.0f, 0.0f);
    up = glm::vec3(0.0f, 0.0f, 1.0f);
}

//////////MOVEMENTS OF THE CAMERA////////

void Camera::move(glm::vec3 v) {
    pos += v;
}

void Camera::moveFPS(float f_b, float r_l, float u_d, float timeDif) {
    move(
            glm::vec3(eye.x * camVelocity * timeDif * f_b - eye.y * camVelocity * timeDif * r_l,
                      eye.y * camVelocity * timeDif * f_b + eye.x * camVelocity * timeDif * r_l,
                      eye.z * camVelocity * timeDif * f_b + camVelocity * timeDif * u_d));
}

void Camera::rotateCenter(float ang_xy, float ang_z, float length) {
    //	pos.vx = length*cos(ang_z)*cos(ang_xy) + eye.vx;
    //	pos.vy = length*cos(ang_z)*sin(ang_xy) + eye.vy;
    //	pos.vz = length*sin(ang_z) + eye.vz;
    //	view = lookAt(vec3(cam.getPos()), vec3(cam.getPosFocus()), vec3(0.0, 0.0, 1.0));
}

void Camera::rotateFoco(float ang_xy, float ang_z, float timeDif) {
    eye = glm::vec3(
            glm::vec4(eye, 1.0f) * rotate(glm::mat4(1.0f), ang_xy * camSensibility * timeDif, glm::vec3(0, 0, 1)));
    eye = glm::vec3(
            glm::vec4(eye, 1.0f)
            * rotate(glm::mat4(1.0f), ang_z * camSensibility * timeDif, glm::vec3(eye.y, -eye.x, 0)));
    if ((eye.z > 0.99f) || (eye.z < -0.99f))
        eye = glm::vec3(
                glm::vec4(eye, 1.0f)
                * rotate(glm::mat4(1.0f), ang_z * camSensibility * timeDif * (-1),
                         glm::vec3(eye.y, -eye.x, 0)));
    eye = normalize(eye);
}

void Camera::pan(float x, float y) {

}

void Camera::linkCamAttrib(GLuint shader) {
    camPosAttrib = glGetUniformLocation(shader, "camPos");
    if (camPosAttrib < 0) {
        printf("Shader did not contain the 'camPos' uniform.");
    }
    camEyeAttrib = glGetUniformLocation(shader, "camEye");
    if (camEyeAttrib < 0) {
        printf("Shader did not contain the 'camEye' uniform.");
    }
    viewAttrib = glGetUniformLocation(shader, "view");
    if (viewAttrib < 0) {
        printf("Shader did not contain the 'view' uniform.");
    }
    projectionAttrib = glGetUniformLocation(shader, "projection");
    if (projectionAttrib < 0) {
        printf("Shader did not contain the 'projection' uniform.");
    }
}

void Camera::loadCamAttrib() {
    glUniform3f(camPosAttrib, pos.x, pos.y, pos.z);
    glUniform3f(camEyeAttrib, eye.x, eye.y, eye.z);
    glUniformMatrix4fv(viewAttrib, 1, GL_FALSE, value_ptr(getViewMatrix()));
    glUniformMatrix4fv(projectionAttrib, 1, GL_FALSE,
                       value_ptr(getProjectionMatrix()));
}

std::string Camera::toString(int tabLevel) {
    std::stringstream tab;
    std::stringstream ss;
    for (int i = 0; i < tabLevel; ++i) {
        tab << "\t";
    }
    ss << tab.str() << "Camera Data" << "\n";
    ss << tab.str() << "Pos = " << vec3ToString(this->pos) << "\n";
    ss << tab.str() << "Eye = " << vec3ToString(this->eye) << "\n";
    ss << tab.str() << "Up = " << vec3ToString(this->up) << "\n";
    return ss.str();
}



