#include <core/InputManager.h>
#include <iostream>


InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::setButton(int value) {
	isClicked = value;
}

void InputManager::setMousePosX(int value) {
	posX = value;
}

void InputManager::setMousePosY(int value) {
	posY = value;
}

int InputManager::getButton() {
	return isClicked;
}

int InputManager::getMousePosX() {
	return posX;
}

int InputManager::getMousePosY() {
	return posY;
}