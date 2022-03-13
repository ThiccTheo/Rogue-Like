#pragma once
#include "Common.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Player.h"

class GUI {
public:
	//UAD - update and draw
	static void draw();
	static void init();
private:
	static Font VCR_OSD_Mono;
	static Font Big_Pixel;

	static Text healthTxt;
	static Texture healthTexture;
	static Sprite healthSprite;
	static void initHealth();
	static void drawHealth();
};