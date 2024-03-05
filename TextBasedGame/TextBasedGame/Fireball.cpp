#include "Fireball.h"
#include <iostream>

Fireball::Fireball() : Spell{20, String("Fireball"), true, 
String("Deals a large amount of damage to the specified target. Costs 20MP")}
{

}

void Fireball::Cast(Game* game, Player* pPlayer)
{
	std::vector<Enemy*> enemies = game->GetRoom(pPlayer->GetPosition()).GetEnemies();

	int target = game->m_target - 1;

	// Deal damage to the enemy in the room
	Enemy* enemy = enemies[target];
	int damage = 0.5f * pPlayer->GetMaxMP() + rand() % 8 - 4;
	int actualDamageDealt = enemy->OnAttacked(damage);

	// Print result of attack
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
		"You send a massive fireball hurling at the " << enemy->GetName() << 
		" and it takes " << RED << actualDamageDealt << " damage." << RESET_COLOR << std::endl ;
	if (enemy->IsAlive()) {
		std::cout << INDENT << "The " << enemy->GetName() << " has " << enemy->GetHP()
			<< " health remaining." << std::endl;
	}
	else {
		enemy->OnDeath(game);
	}
}
