#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
using namespace std;
using namespace sf;

// class Player: Stores the necessary data to control the player
class Player {
private:
	// Player sprite
	Sprite s;
	// Player texture
	Texture t;
	// How far the player can move each frame
	const float DISTANCE = 5.0;
	// How big (wide) the player is
	const int SIZE = 40;
public:
	// Constructor
	Player() {
		// Attempt to load the player texture
		if (!t.loadFromFile("player.png")) {
			cout << "Unable to load player texture!" << endl;
			exit(EXIT_FAILURE);
		}
		// Set the texture for the player sprite
		s.setTexture(t);
	}

	// void setPosition(): Set the player's current position. (Used to reset position to center)
	void setPosition(Vector2f pos) {
		s.setPosition(pos);
	}

	// void move(): Check the keyboard left and right arrows and move the player accordingly.
	// We take the screen width as a parameter so we don't go off the edge of the screen.
	void move(int screenWidth = 800) {
		// If left is pressed and moving further left would not put the player out of bounds, move left
		if (Keyboard::isKeyPressed(Keyboard::Left) && s.getPosition().x >= DISTANCE) {
			s.move(-DISTANCE, 0);
		}
		// If right is pressed and moving further right would not put the player out of bounds, move right
		else if (Keyboard::isKeyPressed(Keyboard::Right) && s.getPosition().x <= screenWidth - SIZE - DISTANCE) {
			s.move(DISTANCE, 0);
		}
	}

	// Vector2f fire(): Returns a Vector2f of where to put a player projectile based on the player's position.
	Vector2f fire() {
		return s.getPosition() - Vector2f(0, 25);
	}

	// void draw(): Draw the player sprite.
	void draw(RenderWindow& w) {
		w.draw(s);
	}

	// Sprite getSprite(): Returns the player sprite. (Used for collision detection)
	Sprite getSprite() {
		return s;
	}
};