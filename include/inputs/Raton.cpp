#include <iostream>
#include "Raton.hpp"

Raton::Raton() :
        x(0), y(0),
        leftButton(false), rightButton(false), middleButton(false),
        capturePointer(true) {
}

Raton::Raton(int valX, int valY) :
        x(valX), y(valY),
        leftButton(false), rightButton(false), middleButton(false),
        capturePointer(true) {
}

void Raton::getPointer(int &valX, int &valY) {
    valX = x;
    valY = y;
}

int Raton::getPointerX() {
    return x;
}

int Raton::getPointerY() {
    return y;
}

int Raton::getCenterPointerX(int w) {
    return x - w / 2.0f;
}

int Raton::getCenterPointerY(int h) {
    return y - h / 2.0f;
}

bool Raton::getCapturePointer() {
    return capturePointer;
}

void Raton::toggleCapturePointer() {
    capturePointer = !capturePointer;
}

void Raton::setPointer(int valX, int valY) {
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
    x = y = 0;
    leftButton = rightButton = middleButton = false;
}

void Raton::setWheel(int wheel, int direction, int x, int y) {
    this->wheel = direction;
}

void Raton::resetWheel() {
    wheel = 0;
}




