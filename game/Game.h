#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "UI.h"
#include "EnemyGroup.h"
#include "Player.h"
#include "ProjectileGroup.h"
using namespace std;
using namespace sf;

// class Game: Master class that stores everything the game needs to run
class Game {
private:
	// UI when in a level
	GameUI gameUI;
	// UI when not in a level
	MenuUI menuUI;
	// Background sprite
	Sprite bg;
	// Texture for background
	Texture bgTexture;
	// Group of enemies
	EnemyGroup eg;
	// Player
	Player player;
	// Group of enemy projectiles
	EnemyProjectileGroup epg;
	// Group of player projectiles
	PlayerProjectileGroup ppg;
	// Counter for number of frames drawn (used as a timer)
	int frameCount;
	// Bool representing whether or not we are in a level
	bool inGame;
	// Current level (1 or 2)
	int currLevel;
	// Current number of lives the player has
	int playerLives;
public:
	// Constructor
	Game() {
		// Initialize frame counter
		frameCount = 0;
		// Seed random number generator
		srand(time(0));
		// Attempt to load background texture
		if (!bgTexture.loadFromFile("gameBG.png")) {
			cout << "Unable to load background texture!" << endl;
			exit(EXIT_FAILURE);
		}
		// Set background texture
		bg.setTexture(bgTexture);
		// Scale up background to fit screen
		bg.setScale(3, 3);
		// Initialize inGame to false (we do not start in a level, we must click START first)
		inGame = false;
		// When we do start a level, we should start on level 1
		currLevel = 1;
		// Give the player 5 lives
		playerLives = 5;
	}

	// void resetGame(): Reset the entire game to its initial state.
	void resetGame() {
		// Reset level to 1
		currLevel = 1;
		// Reset player lives to 5
		playerLives = 5;
		// Reset the level
		resetLevel();
		// Reset the UI
		gameUI.resetGame();
	}

	// void resetLevel(): Reset the current level.
	void resetLevel() {
		// Reset the player's position
		player.setPosition(Vector2f(380, 500));
		// If there are any enemies, clear them out
		eg.clear();
		// Add a new row of enemies
		eg.addRow(100, currLevel);
		// Clear off any enemy projectiles
		epg.clear();
		// Clear off any player projectiles
		ppg.clear();
	}

	// void playerFire(): When the spacebar is pressed, tell the player to fire.
	void playerFire() {
		ppg.add(player.fire());
	}

	// void move(): Move everything in the game.
	void move() {
		// Only move stuff if we are actually in a level.
		if (inGame) {
			// Fire enemy projectiles on a timer.
			// Executes every (180 / currLevel) frames, so every 3 seconds on level 1 and every 1.5 seconds on level 2.
			if (frameCount % (180 / currLevel) == 0) {
				epg.add(eg.fire());
			}
			// Move the enemy projectiles
			epg.move();
			// Move the player
			player.move();
			// Move the player projectiles
			ppg.move();
			// Move the enemies
			eg.move();
			// Detect collision between player projectiles and enemy projectiles
			ppg.detectCollision(epg);
			// Detect collision between player projectiles and enemies, store the number of enemies defeated to add to the score
			int enemiesDefeated = ppg.detectCollision(eg);
			// For every enemy defeated, add 1 to the score in the UI
			for (int i = 0; i < enemiesDefeated; i++) {
				gameUI.incrementScore();
			}
			// If there are no enemies on screen, advance to next level
			if (eg.isEmpty()) {
				// If we are not on the last level, advance the level and return to the menu
				if (currLevel < 2) {
					currLevel++;
					inGame = false;
					menuUI.setCurrState(" LEVEL " + to_string(currLevel));
				}
				// Otherwise, we just completed the last level and need to display a victory screen
				else {
					inGame = false;
					menuUI.setCurrState(" VICTORY!");
					resetGame();
				}
			}
			// Death condition (either the enemies have reached the bottom of the screen or one of the enemy projectiles has collided with the player)
			else if (eg.getYPosition() > 460 || epg.detectCollision(player.getSprite())) {
				// Remove one of the player's lives
				playerLives--;
				// Update the UI lives counter
				gameUI.decrementLives();
				// If the player has no lives left, display a game over and send them back to level 1
				if (playerLives == 0) {
					inGame = false;
					menuUI.setCurrState("GAME OVER");
					resetGame();
				}
				// Otherwise, just reset the current level
				else {
					resetLevel();
				}
			}
		}
	}

	// void draw(): Draw all the sprites for the game.
	void draw(RenderWindow& w) {
		w.draw(bg);
		if (inGame) {
			epg.draw(w);
			player.draw(w);
			gameUI.draw(w);
			ppg.draw(w);
			eg.draw(w);
		}
		else {
			menuUI.draw(w);
		}
		w.display();
		frameCount++;
	}

	// void handleClick(): Handle a mouse click.
	void handleClick(Vector2f mousePos) {
		// We only care about mouse clicks in the menu, not in a level
		if (!inGame) {
			// Ask the menu UI if the user clicked on the start button, if so, start the level.
			if (menuUI.handleClick(mousePos)) {
				inGame = true;
				resetLevel();
			}
		}
	}
};