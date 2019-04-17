//=========================================================
// This is just the starting point for your final project.
// You are expected to modify and add classes/files as needed.
// The code below is the original code for our first graphics
// project (moving the little green ship). 
//========================================================
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
using namespace std;
using namespace sf; 

//============================================================
// Timothy White - Assignment 8
//============================================================

int main()
{
	// Set window size
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	// Initialize game object and rendering window
	Game game;
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Harbert vs. the MooCows");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::MouseButtonReleased) {
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				game.handleClick(mousePos);
			}
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					game.playerFire();
				}
				
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================
		game.move();
		game.draw(window);

	} // end body of animation loop

	return 0;
}

