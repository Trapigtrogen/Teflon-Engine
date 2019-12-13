#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Functionality {
public:
	Functionality();
	~Functionality();

	int getRandomInt(int start, int end);
	float getRandomFloat(float start, int end);

	std::string loadFile(const std::string fileName);
	void writeFile(const std::string fileName, const std::string string);
private:

};