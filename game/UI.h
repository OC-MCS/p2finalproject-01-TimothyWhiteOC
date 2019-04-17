#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

// class GameUI: Controls the UI while in a level.
class GameUI {
private:
	// Font for text
	Font font;
	// Lives counter
	int lives;
	// Text to display number of lives
	Text livesText;
	// Score counter
	int score;
	// Text to display score
	Text scoreText;
public:
	// Constructor
	GameUI() {
		if (!font.loadFromFile("C:\\Windows\\Fonts\\cour.ttf")) {
			cout << "Unable to load game UI font!" << endl;
			exit(EXIT_FAILURE);
		}
		lives = 5;
		livesText.setFont(font);
		livesText.setString("LIVES: " + to_string(lives));
		livesText.setFillColor(Color::Black);
		livesText.setPosition(50, 20);
		score = 0;
		scoreText.setFont(font);
		scoreText.setString("SCORE: " + to_string(score));
		scoreText.setFillColor(Color::Black);
		scoreText.setPosition(600, 20);
	}

	// void resetGame(): Reset everything to default.
	void resetGame() {
		lives = 5;
		livesText.setString("LIVES: " + to_string(lives));
		score = 0;
		scoreText.setString("SCORE: " + to_string(score));
	}

	// void resetScore(): Reset score to 0.
	void resetScore() {
		score = 0;
		scoreText.setString("SCORE: " + to_string(score));
	}

	// void decrementLives(): Subtract 1 from the number of lives displayed.
	void decrementLives() {
		lives--;
		livesText.setString("LIVES: " + to_string(lives));
	}
	
	// void incrementScore(): Add 1 to score displayed.
	void incrementScore() {
		score++;
		scoreText.setString("SCORE: " + to_string(score));
	}

	// void draw(): Draw the UI to the screen.
	void draw(RenderWindow& w) {
		w.draw(livesText);
		w.draw(scoreText);
	}
};

// class MenuUI: Controls the UI for the menu, when not in a level.
class MenuUI {
private:
	// Font
	Font font;
	// Start button
	RectangleShape startButton;
	// "START" text
	Text startText;
	// Text displaying current state (above start button)
	Text currStateText;
public:
	// Constructor
	MenuUI() {
		if (!font.loadFromFile("C:\\Windows\\Fonts\\cour.ttf")) {
			cout << "Unable to load menu UI font!" << endl;
			exit(EXIT_FAILURE);
		}
		startText.setString("START");
		startText.setFont(font);
		startText.setFillColor(Color::Black);
		startText.setPosition(360, 280);
		startButton.setOutlineColor(Color::Black);
		startButton.setOutlineThickness(5);
		startButton.setFillColor(Color::Transparent);
		startButton.setSize(Vector2f(200, 50));
		startButton.setPosition(300, 275);
		currStateText.setString(" LEVEL 1");
		currStateText.setFont(font);
		currStateText.setFillColor(Color::Black);
		currStateText.setPosition(320, 200);
	}

	// void draw(): Draw the UI to the screen.
	void draw(RenderWindow& w) {
		w.draw(currStateText);
		w.draw(startButton);
		w.draw(startText);
	}

	// void setCurrState(): Update the current state text with the provided string.
	void setCurrState(string s) {
		currStateText.setString(s);
	}

	// bool handleClick(): Returns true if the mouse is over the start button when it is clicked.
	bool handleClick(Vector2f mousePos) {
		return startButton.getGlobalBounds().contains(mousePos);
	}
};