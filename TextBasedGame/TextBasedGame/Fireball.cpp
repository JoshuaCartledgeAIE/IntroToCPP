#include "Fireball.h"
#include <iostream>

Fireball::Fireball() : Spell{20, String("Fireball"), true, 
String("Deals a large amount of damage to a single enemy. Costs 20MP")}
{

}

Fireball::~Fireball()
{
}

void Fireball::Cast(Game* game, Player* pPlayer)
{
	// Deal damage to the enemy in the room
	Enemy* enemy = game->GetRoom(pPlayer->GetPosition()).GetEnemy();
	int damage = enemy->OnAttacked(0.5f * pPlayer->GetMaxMP() + rand() % 8 - 4);

	// Print result of attack
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
		"You send a massive fireball hurling at the enemy and it takes " <<
		RED << damage << " damage." << RESET_COLOR << std::endl << INDENT;
	if (enemy->IsAlive()) {
		std::cout << "The enemy has " << enemy->GetHP() << " health remaining." << std::endl;
	}
	else {
		std::cout << GREEN << "You killed the enemy!" << RESET_COLOR << std::endl;
	}
}