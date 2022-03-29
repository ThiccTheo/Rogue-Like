#pragma once
#include "../../vendor/Vendor.h"
#include "../game/Common.h"

class GUI {
public:
	static void draw();
	static void init();
private:
	static Font Big_Pixel;

	static Text healthTxt;
	static Texture healthTexture;
	static Sprite healthSprite;
	static void initHealth();
	static void drawHealth();

	static RectangleShape xpBar;
	static RectangleShape xpBarOutline;
	static void initXP();
	static void drawXP();

	static Vector2f screenOrigin;
};