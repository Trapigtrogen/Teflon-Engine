#pragma once
class InputManager {
public:
	InputManager();
	~InputManager();

	void setButton(int btn, int value);
	void setMousePosX(int value);
	void setMousePosY(int value);

	int getButton();
	int getMousePosX();
	int getMousePosY();

private:
	int posX;
	int posY;
};

