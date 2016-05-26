
#pragma once

struct Raton {
	int x, y;
	bool leftButton, rightButton, middleButton;
	bool capturePointer;
	int wheel;
	Raton();
	Raton(int valX, int valY);
	void getPointer(int &valX, int &valY);
	int getPointerX();
	int getPointerY();
	int getCenterPointerX(int w);
	int getCenterPointerY(int h);
	bool getCapturePointer();
	void toggleCapturePointer();

	void setPointer(int valX, int valY);
	void getButtons(bool &leftButton, bool &rightButton, bool &middleButton);
	void setButtons(bool leftButton, bool rightButton, bool middleButton);
	void setWheel(int wheel, int direction, int x, int y);
	void resetWheel();

	void reset();
};
