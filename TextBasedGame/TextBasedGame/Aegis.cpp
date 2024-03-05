#include "Aegis.h"
#include "Player.h"

Aegis::Aegis() : Spell{ 10, String("Aegis"), true,
String("Blocks up to 20 damage of the enemy's next attack. Costs 10MP.") }
{
}

void Aegis::Cast(Game* game, Player* pPlayer)
{
	// Give player 20 block this turn
	std::cout << EXTRA_OUTPUT_POS << BLUE <<
		"A shield coalesces around you, protecting you from the enemy's attack." << RESET_COLOR << std::endl;
	pPlayer->SetBlock(20);
}
