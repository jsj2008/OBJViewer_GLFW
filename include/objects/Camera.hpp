/*
 * Camera.hpp
 *
 *  Created on: 7/3/2015
 *      Author: JAVIER
 */

#pragma once

#include "glm/glm/vec3.hpp"
#include "glm/glm/mat4x4.hpp"
//#include <glew.h>
#include <string>
#include <libs/lib/glew.h>

struct Camera {

    glm::vec3 pos, eye, up;
    int width, height;
    float FOV;
    float nearClipPlane, farClipPlane;
    float camVelocity;
    float camSensibility;
    GLuint projectionAttrib, viewAttrib, camEyeAttrib, camPosAttrib;

    Camera();
    Camera(const Camera &cam);
    ~Camera();

    glm::vec3 getPos();
    glm::vec3 getFocus();
    glm::vec3 getPosFocus();
    glm::vec3 getUp();

    int getWidth();
    int getHeight();
    float getFOV();
    float getNearClipPlane();
    float getFarClipPlane();
    float getCamSensibility();
    float getCamVelocity();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setPos(glm::vec3 v);
    void setFocus(glm::vec3 v);
    void setUp(glm::vec3 v);
    void setWidth(int w);
    void setHeight(int h);
    void setFOV(float fov);
    void setNearClipPlane(float near);
    void setFarClipPlane(float far);
    void setCamSensibility(float camSens);
    void setCamVelocity(float camVel);

    void reset();

    void move(glm::vec3 v);
    void moveFPS(float f_b, float r_l, float u_d, float timeDif);
    void rotateCenter(float ang_xy, float ang_z, float length);
    void rotateFoco(double ang_xy, double ang_z, float timeDif);
    void pan(float x, float y);

    void linkCamAttrib(GLuint shader);
    void loadCamAttrib();

    std::string toString(int tabLevel);
};

