#include "TurretGame.h"

TurretGame::TurretGame(const String& gameName, Adafruit_SSD1306& display, int& selection, bool& btnState)
	: Game(gameName, display, selection, btnState)
{
}

void TurretGame::init() {
	Game::init();
	selection = 0;
	angle = 0;
}

void TurretGame::update() {
    Game::update();

    int centerX = display.width() / 2;
    int centerY = display.height() / 2;

    angle = (float)selection / ROTARY_ENCODER_STEP * 360.0f;

    Vector2 direction(cos(angle * DEG_TO_RAD), sin(angle * DEG_TO_RAD));


    display.drawLine(centerX, centerY,
        centerX + direction.x * TURRET_LENGTH,
        centerY + direction.y * TURRET_LENGTH,
        WHITE);
}

