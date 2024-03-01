#include "IceShield.h"
#include "Player.h"

IceShield::IceShield() : Spell{ 10, String("Ice Shield"), true,
String("Blocks up to 20 damage of the enemy's next attack. Costs 10MP.") }
{
}

void IceShield::Cast(Game* game, Player* pPlayer)
{
	// Give player 20 block this turn
	std::cout << EXTRA_OUTPUT_POS << BLUE <<
		"An icy shield coalesces around you, shielding you from the enemy's attack." << RESET_COLOR << std::endl;
	pPlayer->SetBlock(20);
}
