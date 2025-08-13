#include "CounterGame.h"

CounterGame::CounterGame(const String& gameName, Adafruit_SSD1306& display, int& selection, bool& btnState)
	: Game(gameName, display, selection, btnState)
{
	counter = 0;
}

void CounterGame::init() {
	Game::init();
	selection = 0;
}

void CounterGame::update() {
	Game::update();
	display.println("Your are at: " + String(counter + selection));
}

void CounterGame::quit() {
	Game::quit();
	counter += selection;
}

