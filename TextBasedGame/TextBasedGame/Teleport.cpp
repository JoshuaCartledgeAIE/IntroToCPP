#include "Teleport.h"
#include <iostream>
#include <algorithm>
#include "GameDefines.h"

Teleport::Teleport() : Spell{ 15, String("Teleport"), false,
String("Teleports the player to a random room. Costs 15MP") }
{
}

Teleport::~Teleport()
{
}

void Teleport::Cast(Game* game, Player* pPlayer)
{
	// Set player to random position within 3 rooms of the player
	int newX = rand() % 6 + std::min(std::max(pPlayer->GetPosition().x, 3), MAZE_WIDTH - 3) - 3;
	int newY = rand() % 6 + std::min(std::max(pPlayer->GetPosition().y, 3), MAZE_HEIGHT - 3) - 3;

	pPlayer->SetPosition({newX, newY});

	std::cout << EXTRA_OUTPUT_POS << MAGENTA <<
		"You experience a nauseating sensation as you are suddenly dematerialized, but luckily you do snap back to reality eventually."
		<< std::endl << INDENT << "After coming to your senses, you find yourself in a completely random room." << RESET_COLOR;
}
