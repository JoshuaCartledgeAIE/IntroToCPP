#include "LightningBolt.h"
#include <iostream>

LightningBolt::LightningBolt() : Spell{5, String("Lightning Bolt"), true,
String("Deals a medium amount of damage to the enemy. Costs 5MP")}
{
}

void LightningBolt::Cast(Game* game, Player* pPlayer)
{
	// Deal damage to the enemy in the room
	Enemy* enemy = game->GetRoom(pPlayer->GetPosition()).GetEnemy();
	int damage = enemy->OnAttacked(0.25f * pPlayer->GetMaxMP() + rand() % 4 - 2);
	
	// Print result of attack
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
		"You blast the enemy with a bolt of lightning and it takes " <<
		RED << damage << " damage." << RESET_COLOR << std::endl << INDENT;
	if (enemy->IsAlive()) {
		std::cout << "The enemy has " << enemy->GetHP() << " health remaining." << std::endl;
	}
	else {
		std::cout << GREEN << "You killed the enemy!" << RESET_COLOR << std::endl;
	}
		 
}
