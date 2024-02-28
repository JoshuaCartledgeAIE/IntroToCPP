#include <iostream>
#include <windows.h>
#include <time.h>
#include <random>
#include "String.h"
#include "Point2D.h"
#include "GameDefines.h"
#include "Game.h"
#include "Player.h"
#include "Room.h"

int main() {

	// Initialise game instance and run startup function
	Game game;

	if (game.Startup() == false) return 1;

	std::cout << TITLE << YELLOW << "MYSTICAL MURDER MAZE" << RESET_COLOR;
	
	while (!game.IsGameOver()) {
		// Main game loop
		game.Draw();

		game.Update();
	}

	// Game has ended
	return 0;
}





