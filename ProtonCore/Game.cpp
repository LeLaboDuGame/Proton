#include "Game.h"



Game::Game(const String& gameName, Adafruit_SSD1306& display, int& selection, bool& btnState) : gameName(gameName), display(display), selection(selection), btnState(btnState){
}

void Game::init() {
	isQuit = false;
	Serial.println("The game: " + gameName + " has been init !");
}

void Game::update() {

}

void Game::quit() {
	isQuit = true;
}



struct Vector2 {
    float x, y;

    Vector2(float _x = 0, float _y = 0) : x(_x), y(_y) {}

    // Opérateurs
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    // Opérateurs d'affectation
    Vector2& operator+=(const Vector2& other) {
        x += other.x; y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x; y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar; y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        x /= scalar; y /= scalar;
        return *this;
    }
};
