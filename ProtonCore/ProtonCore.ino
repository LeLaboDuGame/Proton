#include "games/CounterGame.h"
#include "games/TurretGame.h"
#include "Game.h"
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

// pin of the rotary encoder
#define pinA 26 // CLK
#define pinB 27 // DT

#define pinBtn 32 // pin of the button

const int WIDTH = 128; // number of pixel width
const int HEIGHT = 64; // number of pixel height

const int LOADED_GAME = 3; // Number of game actually loaded !

const long THRESHOLD_TIME_ROTARY_ENCODER = 20; // Time in mili seconds before a new input can be read by the rotary encoder
const long EXIT_TIME = 5000; // Time pressing the btn until the game exit in mili seconds

long lastUpdateRotaryEncoder = 0;

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

int selection = 0;
bool btnState;


Game* games[LOADED_GAME] = { new CounterGame("CounterGame 1", display, selection, btnState), new CounterGame("CounterGame 2", display, selection, btnState), new TurretGame("Turret Game", display, selection, btnState)};
Game* currentGame = nullptr;

volatile int encoderPos = 0;
volatile int lastEncoded = 0;

static int lastEncoderPos = 0;


bool isSelectGameMenuOpen = false;

long exitTimer;

void IRAM_ATTR  onChangeRotaryEncoderState() {
	int MSB = digitalRead(pinA);
	int LSB = digitalRead(pinB);
	int encoded = (MSB << 1) | LSB;
	int sum = (lastEncoded << 2) | encoded;

	// Waiting for a full rotation
	if (encoded == 0b00) {
		if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) // Increment
			encoderPos++;
		else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) // Decrement
			encoderPos--;
	}
	lastEncoded = encoded;
}

void setup() {
	Serial.begin(115200); // Init the comunication

	Serial.println("\n\nStarting Proton...");

	// init pin rotary encoder
	pinMode(pinBtn, INPUT);
	pinMode(pinA, INPUT_PULLUP);
	pinMode(pinB, INPUT_PULLUP);

	lastUpdateRotaryEncoder = millis(); // Update the last time rotaryEncoderWasModified
	exitTimer = millis();


	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
		error("Failed to init the display! Maybe change the display to 0x3D?");
	}
	else {
		Serial.println("Display initialized!");
	}

	// Attach Interupt
	attachInterrupt(digitalPinToInterrupt(pinA), onChangeRotaryEncoderState, CHANGE);   // CHANGE => détecte tout changement d'état
	attachInterrupt(digitalPinToInterrupt(pinB), onChangeRotaryEncoderState, CHANGE);   // CHANGE => détecte tout changement d'état



	// Watermark
	initMessage();
	Serial.println("Starting the os!");
}



void initMessage() {
	display.clearDisplay();
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	display.setTextSize(2);
	display.println("Proton OS");

	display.setTextSize(1);
	display.setCursor(0, 45);
	display.println("Created by LABO");

	display.display();
	delay(2000);
}

void error(char msg[]) {
	Serial.println("ERROR: " + String(msg));
}

void resetScreen() {
	display.clearDisplay();
	display.setCursor(0, 0);
	display.setTextSize(1);
	display.setTextColor(WHITE);
}

void selectGameMenu() {
	isSelectGameMenuOpen = true;
	display.println("Game List:");

	// Verify selection is no over the range
	if (selection > LOADED_GAME - 1) {
		selection = 0;
	}
	else if (selection < 0) {
		selection = LOADED_GAME - 1;
	}

	// print at screen
	for (int i = 0; i < LOADED_GAME; i++) {
		Game game = *games[i];
		display.println(game.gameName + ((i == selection) ? "+" : ""));
	}

	// Load the game
	if (btnState) { 
		currentGame = games[selection];
		isSelectGameMenuOpen = false;
		selection = 0;
		exitTimer = millis(); // set the exitTimer to prevent instant quitting
		currentGame->init();
	}

	// Print msg if no game is loaded
	if (LOADED_GAME <= 0) {
		display.println("No loaded game ! Modify the ProtonCore.ino");
		Serial.println("No loaded game ! Modify the ProtonCore.ino ! Modify LOADED_GAME > 0 and add some games in games variable!");
	}
}

void loop() {
	resetScreen();

	selection += encoderPos - lastEncoderPos;
	lastEncoderPos = encoderPos;

	btnState = !digitalRead(pinBtn); // Read the btn state and inverse the btnState to 

	

	if (currentGame == nullptr) // if no game is load
	{
		if (!isSelectGameMenuOpen) {
			selection = 0;
		}
		// Open the selecting game menu !
		selectGameMenu();
	}
	else if(!currentGame->isQuit) {
		currentGame->update();
		if (btnState) {
			if (millis() - EXIT_TIME >= exitTimer) { // if we pressed the btn during the EXIT TIME
				currentGame->isQuit = true;
			}
		}
		else {
			exitTimer = millis();
		}
	}
	else if(!btnState){ // If quitting the game check if the btn is not pressed
		currentGame->quit();
		currentGame = nullptr;
	}
	else {
		display.println("Game quit: Unepressed the btn");
		display.print("Love your self !");
	}
	display.display();

}
