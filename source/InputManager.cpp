#include <core/InputManager.h>
#include <iostream>


InputManager::InputManager() {
	buttons.resize(0xFE);
}

InputManager::~InputManager() {}


void InputManager::setButton(int value) {
	isClicked = value;
}

void InputManager::setKey(int index, int value) {
	buttons[index] = value;
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

int InputManager::getKey(int index) {
	return buttons[index];
}

int InputManager::getMousePosX() {
	return posX;
}

int InputManager::getMousePosY() {
	return posY;
}