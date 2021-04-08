#include "Input.h"
#include <stdio.h>

Input::Input() {
	wKeyPressed = false;
	aKeyPressed = false;
	dKeyPressed = false;
}

bool Input::getKeyPressed(Key k) {
	bool retVal;
	if (k == Key::W) {
		retVal = wKeyPressed;
	}
	else if (k == Key::A) {
		retVal = aKeyPressed;
	}
	else {
		retVal = dKeyPressed;
	}
	return retVal;
}

void Input::setKeyPressed(Key k, bool value) {
	if (k == Key::W) {
		wKeyPressed = value;
	}
	else if (k == Key::A) {
		aKeyPressed = value;
	}
	else if (k == Key::D) {
		dKeyPressed = value;
	}
}