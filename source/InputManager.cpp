#include <core/InputManager.h>
#include <iostream>


InputManager::InputManager() {
	buttons.resize(0xFE);
}

InputManager::~InputManager() {}


void InputManager::setButton(bool value) {
	isClicked = value;
}

void InputManager::setKey(int index, bool value) {
	buttons[index] = value;
}

void InputManager::setMousePosX(float value) {
	posX = value;
}

void InputManager::setMousePosY(float value) {
	posY = value;
}

bool InputManager::getButton() {
	return isClicked;
}

bool InputManager::getKey(int index) {
	return buttons[index];
}

float InputManager::getMousePosX() {
	return posX;
}

float InputManager::getMousePosY() {
	return posY;
}