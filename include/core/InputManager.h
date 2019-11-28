#pragma once
#include<vector>

class InputManager {
public:
	#define WM_KEY_0 0x30
	#define WM_KEY_1 0x31
	#define WM_KEY_2 0x32
	#define WM_KEY_3 0x33
	#define WM_KEY_4 0x34
	#define WM_KEY_5 0x35
	#define WM_KEY_6 0x36
	#define WM_KEY_7 0x37
	#define WM_KEY_8 0x38
	#define WM_KEY_9 0x39
	#define WM_KEY_A 0x41
	#define WM_KEY_B 0x42
	#define WM_KEY_C 0x43
	#define WM_KEY_D 0x44
	#define WM_KEY_E 0x45
	#define WM_KEY_F 0x46
	#define WM_KEY_G 0x47
	#define WM_KEY_H 0x48
	#define WM_KEY_I 0x49
	#define WM_KEY_J 0x4A
	#define WM_KEY_K 0x4B
	#define WM_KEY_L 0x4C
	#define WM_KEY_M 0x4D
	#define WM_KEY_N 0x4E
	#define WM_KEY_O 0x4F
	#define WM_KEY_P 0x50
	#define WM_KEY_Q 0x51
	#define WM_KEY_R 0x52
	#define WM_KEY_S 0x53
	#define WM_KEY_T 0x54
	#define WM_KEY_U 0x55
	#define WM_KEY_V 0x56
	#define WM_KEY_W 0x57
	#define WM_KEY_X 0x58
	#define WM_KEY_Y 0x59
	#define WM_KEY_Z 0x5A


	InputManager();
	~InputManager();

	void setButton(int value);
	void setMousePosX(int value);
	void setMousePosY(int value);
	void setKey(int index, int value);

	int getButton();
	int getKey(int index);
	int getMousePosX();
	int getMousePosY();

private:
	std::vector<int> buttons;

	int posX = 0;
	int posY = 0;
	int isClicked = 0;
};