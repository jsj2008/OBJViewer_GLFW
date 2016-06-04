
#pragma once

struct Raton {
    double x, y, xVel, yVel;
	bool leftButton, rightButton, middleButton;
	bool capturePointer;
	int wheel;
	Raton();
	void getPointer(double &valX, double &valY);
	double getPointerX();
	double getPointerY();
	void getVelPointer(double &valX, double &valY);
	double getVelPointerX();
	double getVelPointerY();
	bool getCapturePointer();
	void toggleCapturePointer();

	void setPointer(double valX, double valY);
	void getButtons(bool &leftButton, bool &rightButton, bool &middleButton);
	void setButtons(bool leftButton, bool rightButton, bool middleButton);
	void setWheel(int wheel, int direction, double x, double y);
	void resetWheel();

	void reset();
};
