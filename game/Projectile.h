#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

// class Projectile: Base class for both enemy projectiles and player projectiles
class Projectile {
private:
	// Projectile sprite
	Sprite s;
	// Speed (how far to move each frame)
	Vector2f moveDist;
public:
	// Constructor
	// Accepts the position, texture, and speed of the projectile.
	Projectile(Vector2f pos, Texture& img, Vector2f moveDistance) {
		s.setPosition(pos);
		s.setTexture(img);
		moveDist = moveDistance;
	}

	// void move(): Move the projectile by the amount defined in moveDist.
	void move() {
		s.move(moveDist);
	}

	// void draw(): Draw the projectile.
	void draw(RenderWindow& w) {
		w.draw(s);
	}

	// bool detectCollision(): Given another sprite, check if the two are touching.
	bool detectCollision(Sprite collider) {
		return s.getGlobalBounds().intersects(collider.getGlobalBounds());
	}

	// Vector2f getPosition(): Returns the current position.
	Vector2f getPosition() {
		return s.getPosition();
	}
	
	// Sprite getSprite(): Returns the sprite. (Used for collision detection)
	Sprite getSprite() {
		return s;
	}
};

// class EnemyProjectile: Represents an enemy projectile. These will move downward (positive y).
class EnemyProjectile : public Projectile {
public:
	// Constructor
	// All we need to do here is initialize the base class
	EnemyProjectile(Vector2f pos, Texture& t) : Projectile(pos, t, Vector2f(0, 10)) {
	}
};

// class PlayerProjectile: Represents a player projectile. These will move upward (negative y).
class PlayerProjectile : public Projectile {
public:
	// Constructor
	// All we need to do here is initialize the base class
	PlayerProjectile(Vector2f pos, Texture& t) : Projectile(pos, t, Vector2f(0, -10)) {
	}
};