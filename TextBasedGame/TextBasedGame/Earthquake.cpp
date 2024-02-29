#include "Earthquake.h"

Earthquake::Earthquake() : Spell{10, String("Earthquake"), false, 
String("Causes an earthquake, forming paths from this room to all surrounding rooms. Costs 10MP.") }
{
}

void Earthquake::Cast(Game* game, Player* pPlayer)
{
	// Adds a transition in all directions in the player's current room
	Room& room = game->GetRoom(pPlayer->GetPosition());
	room.ClearTransitions();
	for (int i = 0; i < 4; i++)
		room.AddTransition(i, game, true);

	std::cout << EXTRA_OUTPUT_POS << MAGENTA <<
		"You feel a jarring tremble beneath your feet, and see several new tunnels open up around you." << RESET_COLOR;
		
}
