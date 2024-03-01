#include "Enemy.h"
#include "Character.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

Enemy::Enemy() : Character{ {0,0}, 40, 15, 5 }, m_nextAttack{ ESCAPE }, m_seqIndex{ 0 }, m_itemDropChance{0}
{
	m_priority = PRIORITY_ENEMY;
}

Enemy::Enemy(Point2D pos, int HP, int AT, int DF, String name, float chance) :
	Character{ pos, HP, AT, DF }, m_name{ name }, m_nextAttack{ESCAPE}, m_seqIndex{ 0 }, m_itemDropChance{chance}
{
	m_priority = PRIORITY_ENEMY;
}

int Enemy::OnAttacked(int damageDealt)
{
	int damage = damageDealt - m_defendPoints;
	if (damage <= 0) damage = rand() % 10 + 1; // if DF was too high, take small random dmg

	SetHP(m_healthPoints - damage);
	return damage;
}

void Enemy::Attack(Player* pPlayer, Game* game)
{
	// Make sure a dead enemy doesn't attack!
	if (!IsAlive()) { return; }

	int damage = 0;
	int index = 0;
	// Act on attack intent
	switch (m_nextAttack)
	{
	case WEAK:
		// deal low amount of damage
		damage = m_attackPoints * 0.75f + (rand() % 4) - 2 - pPlayer->GetDF();
		if (damage <= 0) damage = rand() % 5 + 1; // if player's DF was too high, deal small random dmg
		pPlayer->SetHP(pPlayer->GetHP() - damage);

		// print result of attack
		std::cout << INDENT << "The " << m_name << " hit you with a weak attack, dealing " 
			<< RED << damage << " damage. " << RESET_COLOR << std::endl
			<< INDENT << "You have " << pPlayer->GetHP() << "HP remaining." << std::endl;
		break;

	case MED:
		// deal normal amount of damage
		damage = m_attackPoints + (rand() % 4) - 2 - pPlayer->GetDF();
		if (damage <= 0) damage = rand() % 5 + 1; // if player's DF was too high, deal small random dmg
		pPlayer->SetHP(pPlayer->GetHP() - damage);
		
		// print result of attack
		std::cout << INDENT << "The " << m_name << " hit you with a normal attack, dealing "
			<< RED << damage << " damage. " << RESET_COLOR << std::endl
			<< INDENT << "You have " << pPlayer->GetHP() << "HP remaining." << std::endl;
		break;

	case STRONG:
		// deal high amount of damage
		damage = m_attackPoints * 2 + (rand() % 4) - 2 - pPlayer->GetDF();
		if (damage <= 0) damage = rand() % 5 + 1; // if player's DF was too high, deal small random dmg
		pPlayer->SetHP(pPlayer->GetHP() - damage);

		// print result of attack
		std::cout << INDENT << "The " << m_name << " hit you with a strong attack, dealing "
			<< RED << damage << " damage. " << RESET_COLOR << std::endl
			<< INDENT << "You have " << pPlayer->GetHP() << "HP remaining." << std::endl;
		break;

	case DEBUFF:
		break;

	case HEAL:
		// heal this enemy a large amount
		break;

	case STEAL:
		// pick a random item from player's inventory
		if (pPlayer->m_inventory.size() == 0) { std::cout << INDENT << "The " << m_name << " found nothing to steal!" << std::endl; break; }
		index = rand() % pPlayer->m_inventory.size();
		// notify player of what item was stolen
		std::cout << INDENT << "The " << m_name << " stole your " << YELLOW
			<< pPlayer->m_inventory[index]->GetName() << RESET_COLOR << " from you!" << std::endl;
		// Add it to enemy's inventory
		m_inventory.push_back(pPlayer->m_inventory[index]);
		// Make player lose the benefit of the item
		pPlayer->m_inventory[index]->OnStolen(pPlayer);
		// Remove it from player's inventory
		pPlayer->m_inventory.erase(pPlayer->m_inventory.begin() + index);
		break;

	case ESCAPE:
		// Remove this enemy from its room
		game->GetRoom(m_mapPosition).RemoveGameObject(this);
		std::cout << INDENT << "The " << m_name << " ran away, taking all its stolen items with it!" << std::endl;
		break;

	default:
		break;
	}

	// Switch intent to the next attack in the sequence
	m_seqIndex = (m_seqIndex + 1) % m_attackSequence.size();
	m_nextAttack = m_attackSequence[m_seqIndex];
}

void Enemy::OnDeath(Game* game)
{
	// Let player know that the enemy died
	std::cout << INDENT << GREEN << "You killed the " << m_name << "!" << RESET_COLOR << std::endl << INDENT;
	
	// Either drop an item or some MP
	if ((rand() % 100) / 100.0f < m_itemDropChance) {
		std::cout << YELLOW << "The enemy dropped an item! (use the 'pickup' command to grab it!)" << RESET_COLOR << std::endl;
		game->AddStatItem(m_mapPosition);
	}
	else {
		Player* player = game->GetPlayer();

		// Increase players MP by random amount (capping it at max MP)
		int MPGain = rand() % 5 + 3;
		player->SetMP(player->GetMP() + MPGain);
		std::cout << "You gained " << BLUE << MPGain << "MP!" << RESET_COLOR;
	}
	std::cout << std::endl;

	// check for possible HP gain from harvester's scythe item
	if (game->GetPlayer()->m_gainHPOnKill) {
		int HPGain = rand() % 5 + 1;
		game->GetPlayer()->SetHP(game->GetPlayer()->GetHP() + HPGain);
		std::cout << INDENT << GREEN << "You gained " << HPGain <<
			"HP from the Harvester's Scythe!" << RESET_COLOR << std::endl;
	}

	// Return any stolen items
	if (m_inventory.size() > 0) {
		std::cout << INDENT << "Your stolen items are now returned to you:" << std::endl;
		for (Item* item : m_inventory) {
			game->GetPlayer()->m_inventory.push_back(item);
			item->OnPickup(game->GetPlayer());
		}
	}
}


void Enemy::DrawDescription()
{
	// Delete 2 lines and insert 2 line
	std::cout << CSI << "2M" << CSI << "2L";

	// Print enemy's name and HP
	std::cout << INDENT  << "You stumble upon a vicious " << RED << m_name << RESET_COLOR << " that has " << m_healthPoints << "HP." << std::endl;
	
	// Print enemy's attack intent
	std::cout << INDENT << "The " << RED << m_name << RESET_COLOR << " intends to " << YELLOW;

	switch (m_nextAttack) {
	case WEAK:
		std::cout << "perform a weak attack";
		break;
	case MED:
		std::cout << "perform an average attack";
		break;
	case STRONG:
		std::cout << "perform a strong attack";
		break;
	case DEBUFF:
		std::cout << "apply a temporary debuff to you";
		break;
	case STEAL:
		std::cout << "steal one of your items";
		break;
	case ESCAPE:
		std::cout << "run away with its stolen loot";
		break;
	default:
		std::cout << "do something? I can't tell what though";
		break;
	}
		
		
	std::cout << RESET_COLOR << " next turn." << std::endl;
}

