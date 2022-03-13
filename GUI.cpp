#include "GUI.h"

Font GUI::VCR_OSD_Mono;
Font GUI::Big_Pixel;

Text GUI::healthTxt;
Texture	GUI::healthTexture;
Sprite GUI::healthSprite;

RectangleShape GUI::xpBar;
RectangleShape GUI::xpBarOutline;

void GUI::init() {
	VCR_OSD_Mono.loadFromFile("GUI/VCR_OSD_Mono.ttf");
	Big_Pixel.loadFromFile("GUI/Big_Pixel.otf");

	initHealth();
	initXP();
}

void GUI::draw() {
	drawHealth();
	drawXP();
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

void GUI::initXP() {
	xpBarOutline.setSize(Vector2f(100.f, 10.f));
	xpBarOutline.setFillColor(Color::Black);
	xpBar.setSize(Vector2f(Player::xp * 5.f, 6.f));
	xpBarOutline.setOrigin(0.f, xpBarOutline.getSize().y / 2);
	xpBar.setOrigin(0.f, xpBar.getSize().y / 2);
}

void GUI::drawXP() {
	Vector2f xpBarPosition = Vector2f(Game::window.mapPixelToCoords(Vector2i(60, 12)));
	xpBar.setSize(Vector2f(Player::xp * 10.f, 6.f));
	xpBar.setFillColor(Color(255, 255 - Player::xp * 25, 0));
	xpBarOutline.setPosition(xpBarPosition.x, xpBarPosition.y -0.5f);
	xpBar.setPosition(xpBarOutline.getPosition().x + 2.f, xpBarOutline.getPosition().y);
	Game::window.draw(xpBarOutline);
	Game::window.draw(xpBar);
}