#include "GUI.h"

Font GUI::VCR_OSD_Mono;
Font GUI::Big_Pixel;

Text GUI::healthTxt;
Texture	GUI::healthTexture;
Sprite GUI::healthSprite;

void GUI::init() {
	VCR_OSD_Mono.loadFromFile("Font/VCR_OSD_Mono.ttf");
	Big_Pixel.loadFromFile("Font/Big_Pixel.otf");

	initHealth();
}

void GUI::draw() {
	drawHealth();
}

void GUI::initHealth() {
	healthTexture.loadFromFile("GUI/Health.png");
	healthSprite.setTexture(healthTexture);
	healthTxt.setFont(Big_Pixel);
	healthTxt.setCharacterSize(13);
	healthTxt.setLetterSpacing(0.5);
	healthTxt.setFillColor(Color::White);
	healthTxt.setOutlineColor(Color::Black);
	healthTxt.setOutlineThickness(1.f);
}

void GUI::drawHealth() {
	healthTxt.setString("   x " + to_string(Player::health));
	healthTxt.setPosition(Vector2f(Game::window.mapPixelToCoords(Vector2i(0, 3))));
	healthSprite.setPosition(Vector2f(Game::window.mapPixelToCoords(Vector2i(2, 5))));
	Game::window.draw(healthTxt);
	Game::window.draw(healthSprite);
}