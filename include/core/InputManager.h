#pragma once
class InputManager {
public:
	InputManager();
	~InputManager();

	void setButton(int value);
	void setMousePosX(int value);
	void setMousePosY(int value);

	int getButton();
	int getMousePosX();
	int getMousePosY();

private:
	int posX = 0;
	int posY = 0;
	int isClicked = 0;
};