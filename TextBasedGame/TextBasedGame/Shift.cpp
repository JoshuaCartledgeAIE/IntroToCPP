#include "Shift.h"
#include "Game.h"
#include "GameDefines.h"
#include <iostream>

Shift::Shift() : Spell{10, String("Shift"), false, 
String("Shuffles all paths throughout the maze. Costs 10MP")}
{
}

Shift::~Shift()
{
}

bool Shift::Cast(Game* game, Player* pPlayer)
{
	// Clear map display
	std::cout << MAP_OUTPUT_POS << CSI << "15M" << CSI << "15L";

	// Clear all transitions from all rooms
	for (int i = 0; i < MAZE_HEIGHT * MAZE_WIDTH; i ++) {
		game->GetRoom((int)(i / MAZE_WIDTH), i % MAZE_WIDTH).ClearTransitions();
	}

	// Loop through each room and re-randomise the transitions
	for (int i = 0; i < MAZE_HEIGHT * MAZE_WIDTH; i += 2) {
		game->GetRoom((int)(i / MAZE_WIDTH), i % MAZE_WIDTH).RandomiseTransitions(game);
	}

	game->Draw();

	return true;
}
