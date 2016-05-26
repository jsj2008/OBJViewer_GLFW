/*
 * Teclado.cpp
 *
 *  Created on: 4/8/2015
 *      Author: Javier
 */

#include "Teclado.hpp"
#include <string.h>

Teclado::Teclado() {
    memset(key_state, 0, sizeof(char)*MAX_NUM_KEYS);
}
bool Teclado::getKey(int numKey) {
	return key_state[numKey];
}
void Teclado::setKey(int numKey, bool state) {
	key_state[numKey] = state;
}

void Teclado::reset() {
    memset(key_state, 0, sizeof(char)*MAX_NUM_KEYS);
}

