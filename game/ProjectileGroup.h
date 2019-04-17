#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "EnemyGroup.h"
using namespace std;
using namespace sf;

// class EnemyProjectileGroup: Contains all the enemy projectiles.
class EnemyProjectileGroup {
private:
	// List of enemy projectiles
	list<EnemyProjectile> group;
	// Texture for all the enemy projectiles to share
	Texture t;
public:
	// Constructor
	EnemyProjectileGroup() {
		// Attempt to load enemy projectile texture
		if (!t.loadFromFile("enemyProjectile.png")) {
			cout << "Unable to load enemy projectile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	// void add(): Add a projectile to the list at the specified position.
	void add(Vector2f pos) {
		group.push_back(EnemyProjectile(pos, t));
	}

	// void move(): Move all the projectiles.
	void move() {
		// Start an iterator
		list<EnemyProjectile>::iterator i = group.begin();
		// Loop through entire list
		while (i != group.end()) {
			// Move current projectile
			i->move();
			// If the projectile is off screen, delete it
			if (i->getPosition().y > 600) {
				i = group.erase(i);
			}
			// Otherwise, just advance the iterator
			else {
				i++;
			}
		}
	}

	// void draw(): Draw all the projectiles to the screen.
	void draw(RenderWindow& w) {
		for (list<EnemyProjectile>::iterator i = group.begin(); i != group.end(); i++) {
			i->draw(w);
		}
	}

	// bool detectCollision(): Given a sprite, determine if any of the projectiles are touching it.
	bool detectCollision(Sprite s) {
		// Set a flag for if we have collided with anything
		bool collided = false;
		// Start an iterator
		list<EnemyProjectile>::iterator i = group.begin();
		// Loop as long as we have not yet collided and have not reached the end of the list
		while (!collided && i != group.end()) {
			// If the current projectile is touching the sprite, delete the projectile and set the collided flag to true
			if (i->detectCollision(s)) {
				group.erase(i);
				collided = true;
			}
			// Otherwise, just advance the iterator
			else {
				i++;
			}
		}
		// Return whether anything collided with the sprite
		return collided;
	}

	// void clear(): Delete all the projectiles in the list.
	void clear() {
		group.clear();
	}
};

// class PlayerProjectileGroup: Contains all the player projectiles.
class PlayerProjectileGroup {
private:
	// List of player projectiles
	list<PlayerProjectile> group;
	// Texture for all player projectiles to share
	Texture t;
public:
	// Constructor
	PlayerProjectileGroup() {
		// Attempt to load player projectile texture
		if (!t.loadFromFile("playerProjectile.png")) {
			cout << "Unable to load player projectile texture!" << endl;
			exit(EXIT_FAILURE);
		}
	}

	// void add(): Add a projectile to the list at the given position.
	void add(Vector2f pos) {
		group.push_back(PlayerProjectile(pos, t));
	}

	// void move(): Move all the player projectiles.
	void move() {
		// Start an iterator
		list<PlayerProjectile>::iterator i = group.begin();
		// Loop until the end of the list
		while (i != group.end()) {
			// Move the current projectile
			i->move();
			// If the projectile is off screen, delete it
			if (i->getPosition().y < -40) {
				i = group.erase(i);
			}
			// Oterwise, just advance the iterator.
			else {
				i++;
			}
		}
	}

	// void draw(): Draw all the player projectiles to the screen.
	void draw(RenderWindow& w) {
		for (list<PlayerProjectile>::iterator i = group.begin(); i != group.end(); i++) {
			i->draw(w);
		}
	}

	// int detectCollision(): Given an EnemyGroup, determine if there were any collisions and if so, return how many.
	int detectCollision(EnemyGroup& eg) {
		// Set collision counter
		int collisions = 0;
		// Start an iterator
		list<PlayerProjectile>::iterator i = group.begin();
		// Loop until end of list
		while (i != group.end()) {
			// If any of the enemies collided with the current projectile, delete the projectile and increment the collision counter
			if (eg.detectCollision(*i)) {
				i = group.erase(i);
				collisions++;
			}
			// Otherwise, just advance the iterator
			else {
				i++;
			}
		}
		// Return the number of collisions
		return collisions;
	}

	// void detectCollision(): Given an EnemyProjectileGroup, determine if there were any collisions.
	// This allows player projectiles and enemy projectiles to cancel each other out.
	void detectCollision(EnemyProjectileGroup& epg) {
		// Start an iterator
		list<PlayerProjectile>::iterator i = group.begin();
		// Loop until the end of the list
		while (i != group.end()) {
			// If the current projectile collided with any enemy projectiles, delete it
			if (epg.detectCollision(i->getSprite())) {
				i = group.erase(i);
			}
			// Otherwise, just advance the iterator
			else {
				i++;
			}
		}
	}

	// void clear(): Delete all the projectiles in the list.
	void clear() {
		group.clear();
	}
};