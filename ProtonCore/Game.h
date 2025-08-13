#ifndef GAME_H
#define GAME_H

#include "Arduino.h"
#include <Adafruit_SSD1306.h>

class Game
{
protected:
	Adafruit_SSD1306& display;
	int& selection;
	bool& btnState;
public:
	bool isQuit;

	String gameName;
	Game(const String& gameName, Adafruit_SSD1306& display, int& selection, bool& btnState);
	virtual void init();
	virtual void update();
	virtual void quit();
};

struct Vector2 {
    float x;
    float y;

    // Constructeurs
    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}

    // ----- Opérateurs -----
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

    // ----- Méthodes utiles -----
    float length() const {
        return sqrt(x * x + y * y);
    }

    float lengthSquared() const {
        return x * x + y * y;
    }

    Vector2 normalized() const {
        float len = length();
        if (len != 0) {
            return Vector2(x / len, y / len);
        }
        return Vector2(0, 0);
    }

    void normalize() {
        float len = length();
        if (len != 0) {
            x /= len;
            y /= len;
        }
    }

    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    static float distance(const Vector2& a, const Vector2& b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    static Vector2 zero() {
        return Vector2(0, 0);
    }

    static Vector2 one() {
        return Vector2(1, 1);
    }
};

#endif