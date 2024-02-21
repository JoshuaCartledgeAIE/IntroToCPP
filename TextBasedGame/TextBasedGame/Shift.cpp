#include "Shift.h"
#include "Game.h"

Shift::Shift() : Spell{10, String("Shift"), false, 
String("Shuffles all paths throughout the maze. Costs 10MP")}
{
}

Shift::~Shift()
{
}

bool Shift::Cast(Game* game, Player* pPlayer)
{
	// Check if player has enough mana, and if so, spend the appropriate amount of mana
	if (pPlayer->GetMana() > m_manaCost)


	// Loop through each room and re-randomise the transitions
	for (int i = 0; i < MAZE_HEIGHT * MAZE_WIDTH; i += 2) {
		game->GetRoom((int)(i / MAZE_WIDTH), i % MAZE_WIDTH).RandomiseTransitions(game);
	}
	return true;
}
