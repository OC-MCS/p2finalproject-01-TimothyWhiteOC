#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Projectile.h"
using namespace std;
using namespace sf;

// class EnemyGroup: Contains all the enemies currently on the screen.
class EnemyGroup {
private:
	// List of the enemies
	list<Enemy> group;
	// Texture for all the enemies to share
	Texture t;
public:
	// No constructor necessary, texture will be set and enemies will be added when a level is started

	// void addRow(): Add a row of enemies to the list, given a vertical position and the current level.
	void addRow(int y, int level) {
		// If we are on level 1, attempt to load the level 1 enemy texture.
		if (level == 1) {
			if (!t.loadFromFile("enemy.png")) {
				cout << "Unable to load enemy texture!" << endl;
				exit(EXIT_FAILURE);
			}
		}
		// Otherwise, attempt to load the level 2 enemy texture.
		else {
			if (!t.loadFromFile("enemy2.png")) {
				cout << "Unable to load enemy texture!" << endl;
				exit(EXIT_FAILURE);
			}
		}
		// Add 10 new enemies
		// They will have the same texture, start at the same height, and move at a rate defined by (level / 2) pixels per frame
		for (int i = 0; i < 10; i++) {
			group.push_back(Enemy(t, Vector2f((i+1) * 70, y), level / 2.0));
		}
	}

	// void move(): Move all the enemies.
	void move() {
		for (list<Enemy>::iterator i = group.begin(); i != group.end(); i++) {
			i->move();
		}
	}

	// void draw(): Draw all the enemies to the screen.
	void draw(RenderWindow& w) {
		for (list<Enemy>::iterator i = group.begin(); i != group.end(); i++) {
			i->draw(w);
		}
	}

	// Vector2f fire(): Randomly select an enemy to fire a projectile, then return the starting position for the projectile.
	Vector2f fire() {
		// Randomly select an enemy
		int pos = rand() % group.size();
		// Start an iterator
		list<Enemy>::iterator it = group.begin();
		// Advance the iterator until we reach the previously selected enemy
		for (int i = 0; i < pos; i++) {
			it++;
		}
		// Return the position from the selected enemy's fire function
		return it->fire();
	}

	// bool detectCollision(): Given a projectile, returns whether the projectile has collided with any of the enemies.
	bool detectCollision(Projectile p) {
		// Initialize a collided bool
		bool collided = false;
		// Start an iterator
		list<Enemy>::iterator i = group.begin();
		// Loop as long as we have not yet collided or hit the end of the list
		while (!collided && i != group.end()) {
			// Check if the projectile has collided with the current enemy
			// If so, delete the enemy and set collided to true
			if (p.detectCollision(i->getSprite())) {
				group.erase(i);
				collided = true;
			}
			// Otherwise, just advance the iterator
			else {
				i++;
			}
		}
		// Return whether the projectile collided with anything
		return collided;
	}

	// void clear(): Clear all the enemies in the list.
	void clear() {
		group.clear();
	}

	// bool isEmpty(): Returns true if there are no enemies in the list. (Used to check win condition)
	bool isEmpty() {
		return group.size() == 0;
	}

	// float getYPosition(): Returns the vertical position of the row of enemies. (Used to see if the enemies have reached the bottom of the screen)
	float getYPosition() {
		return group.begin()->getSprite().getPosition().y;
	}
};