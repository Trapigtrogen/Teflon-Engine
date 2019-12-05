#include <core/functionality.h>
#include <iostream>


Functionality::Functionality() {}

Functionality::~Functionality() {}

int Functionality::getRandomInt(int start, int end) {
	return start + rand() % end;
}

float Functionality::getRandomFloat(float start, int end) {
	return start + rand() % end;
}