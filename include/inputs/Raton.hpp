
#pragma once

struct Raton {
	double x, y;
	bool leftButton, rightButton, middleButton;
	bool capturePointer;
	int wheel;
	Raton();
	Raton(double valX, double valY);
	void getPointer(double &valX, double &valY);
	double getPointerX();
	double getPointerY();
	double getCenterPointerX(int w);
	double getCenterPointerY(int h);
	bool getCapturePointer();
	void toggleCapturePointer();

	void setPointer(double valX, double valY);
	void getButtons(bool &leftButton, bool &rightButton, bool &middleButton);
	void setButtons(bool leftButton, bool rightButton, bool middleButton);
	void setWheel(int wheel, int direction, int x, int y);
	void resetWheel();

	void reset();
};
