#ifndef _COUNTERGAME_h
#define _COUNTERGAME_h
#include "../Game.h"

class CounterGame : public Game {
public:
	CounterGame(const String& gameName, Adafruit_SSD1306& display, int& selection, bool& btnState);

	void init() override;

	void update() override;

	void quit() override;

	int counter;
};


#endif