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

	while (!game.IsGameOver()) {
		// Main game loop
		game.Draw();

		game.Update();
	}

	// Game has ended
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return 0;
}





