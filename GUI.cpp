#include "GUI.h"
#include "Game.h"
#include "ResourceManager.h"
#include "Player.h"

Font GUI::VCR_OSD_Mono;
Font GUI::Big_Pixel;

Text GUI::healthTxt;
Texture	GUI::healthTexture;
Sprite GUI::healthSprite;

RectangleShape GUI::xpBar;
RectangleShape GUI::xpBarOutline;

Vector2f GUI::screenOrigin;

void GUI::init() {
	VCR_OSD_Mono.loadFromFile("GUI/VCR_OSD_Mono.ttf");
	Big_Pixel.loadFromFile("GUI/Big_Pixel.otf");

	initHealth();
	initXP();
}

void GUI::draw() {
	screenOrigin = Vector2f((Game::view.getCenter().x - Game::view.getSize().x / 2), (Game::view.getCenter().y - Game::view.getSize().y / 2));
	drawHealth();
	drawXP();
}

void GUI::initHealth() {
	healthTexture.loadFromFile("GUI/Health.png");
	healthSprite.setTexture(healthTexture);
	healthTxt.setFont(Big_Pixel);
	healthTxt.setCharacterSize(14);
	healthTxt.setLetterSpacing(0.5);
	healthTxt.setFillColor(Color::White);
	healthTxt.setOutlineColor(Color::Black);
	healthTxt.setOutlineThickness(1.f);
}

void GUI::drawHealth() {
	healthTxt.setString("   x " + to_string(Player::health));
	healthTxt.setPosition(screenOrigin.x + 4, screenOrigin.y + 3);
	healthSprite.setPosition(screenOrigin.x + 2, screenOrigin.y + 2);
	healthSprite.setScale(1.5, 1.5);
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
	xpBar.setSize(Vector2f(Player::xp * 10.f, 6.f));
	xpBar.setFillColor(Color(255, 255 - Player::xp * 25, 0));
	xpBarOutline.setPosition(screenOrigin.x + 65, screenOrigin.y + 11.f);
	xpBar.setPosition(xpBarOutline.getPosition().x + 2.f, xpBarOutline.getPosition().y);
	Game::window.draw(xpBarOutline);
	Game::window.draw(xpBar);
}