#ifndef _TURRETGAME_h
#define _TURRETGAME_h
 
#include "../Game.h"

class TurretGame : public Game {
private:
	const int TURRET_LENGTH = 4;
	const int ROTARY_ENCODER_STEP = 20; // Modify this by the number of state you have
	static const int TARGET_BUFFER_SIZE = 20;
	const long SPAWN_RATE = 1000; // Spawn rate in mili seconds

	Vector2* target[TARGET_BUFFER_SIZE];
	float angle;


public:
	TurretGame(const String& gameName, Adafruit_SSD1306& display, int& selection, bool& btnState);
	
	void init() override;

	void update() override;

};
#endif

