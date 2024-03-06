#include "Lightning.h"
#include <iostream>
#include <vector>

Lightning::Lightning() : Spell{15, String("Lightning"), true,
String("Deals a medium amount of damage to ALL enemies. Costs 15MP")}
{
}

void Lightning::Cast(Game* game, Player* pPlayer)
{
	// Deal damage to each enemy in the room
	std::vector<Enemy*> enemies = game->GetRoom(pPlayer->GetPosition()).GetEnemies();
	
	std::vector<int> damagesDealt;
	for (Enemy* pEnemy : enemies) {
		int damage = 0.3f * pPlayer->GetMaxMP() + rand() % 4 - 2;
		int actualDamageDealt = pEnemy->OnAttacked(damage);
		damagesDealt.push_back(actualDamageDealt);
	}
	
	
	// Print result of attack
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
		"A bolt of lightning blasts from your fingertips and deals ";
	for (int i = 0; i < enemies.size(); i++) {
		std::cout << RED << damagesDealt[i] << " damage " << RESET_COLOR <<
			"to the " << enemies[i]->GetName();

		// format sentence correctly
		if (i < (int)enemies.size() - 2)
			std::cout << ", ";
		else if (i < (int)enemies.size() - 1)
			std::cout << " and ";
		else
			std::cout << ".";
	}
	std::cout << std::endl;

	// Tell player about any killed enemies
	for (Enemy* pEnemy : enemies) {
		if (!pEnemy->IsAlive()) {
			pEnemy->OnDeath(game);
		}
	}
		 
}
