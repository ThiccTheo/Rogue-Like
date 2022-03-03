#pragma once
#include "Common.h"

class Game {
public:
	static RenderWindow window;
	static View view;
	static RectangleShape cullingPoint;
	static void setup();
private:
	static const float WIDTH;
	static const float HEIGHT;
};