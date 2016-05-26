
#pragma once

const int MAX_NUM_KEYS = 256;

struct Teclado {
	char key_state[MAX_NUM_KEYS];
	Teclado();
	bool getKey(int numKey);
	void setKey(int numKey, bool state);
	void reset();
};
