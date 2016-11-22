#include <iostream>
#include "Raton.hpp"

Raton::Raton() :
        x(0), y(0), xVel(0), yVel(0),
        leftButton(false), rightButton(false), middleButton(false),
        capturePointer(true) {
}

void Raton::getPointer(double &valX, double &valY) {
    valX = x;
    valY = y;
}

double Raton::getPointerX() {
    return x;
}

double Raton::getPointerY() {
    return y;
}

void Raton::getVelPointer(double &valX, double &valY) {
    valX = xVel;
    valY = yVel;
}

double Raton::getVelPointerX() {
    return xVel;
}

double Raton::getVelPointerY() {
    return yVel;
}

bool Raton::getCapturePointer() {
    return capturePointer;
}

void Raton::toggleCapturePointer() {
    capturePointer = !capturePointer;
}

void Raton::setPointer(double valX, double valY) {
    xVel = x - valX;
    yVel = y - valY;
//    xVel *= -1;
//    yVel *= -1;
    x = valX;
    y = valY;
}

void Raton::getButtons(bool &lButton, bool &rButton, bool &mButton) {
    leftButton = lButton;
    rightButton = rButton;
    middleButton = mButton;
}

void Raton::setButtons(bool lButton, bool rButton, bool mButton) {
    lButton = leftButton;
    rButton = rightButton;
    mButton = middleButton;
}

void Raton::reset() {
    x = y = xVel = yVel = 0;
    leftButton = rightButton = middleButton = false;
}

void Raton::setWheel(int wheel, int direction, double x, double y) {
    this->wheel = direction;
}

void Raton::resetWheel() {
    wheel = 0;
}




