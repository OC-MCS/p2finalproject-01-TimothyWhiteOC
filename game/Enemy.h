#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
using namespace std;
using namespace sf;

// class Enemy: Represents a single enemy on the screen.
class Enemy {
private:
	// Enemy sprite
	Sprite s;
	// How far the enemy will move each frame
	Vector2f moveDist;
public:
	// Constructor
	// Accepts the texture, position, and downward speed of the enemy.
	Enemy(Texture& t, Vector2f pos, float speed = 1) : moveDist(0, speed) {
		s.setTexture(t);
		s.setPosition(pos);
	}

	// void move(): Move the enemy downward by moveDist.
	void move() {
		s.move(moveDist);
	}

	// void draw(): Draw the enemy to the screen.
	void draw(RenderWindow& w) {
		w.draw(s);
	}

	// Vector2f fire(): When this enemy needs to shoot a projectile, returns the position of where the projectile will be fired from.
	Vector2f fire() {
		return s.getPosition() + Vector2f(0, 25);
	}

	// Sprite getSprite(): Returns the enemy sprite. (Used for collision detection)
	Sprite getSprite() {
		return s;
	}
};