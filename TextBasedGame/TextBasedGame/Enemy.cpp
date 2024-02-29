#include "Enemy.h"
#include "Character.h"
#include "Game.h"
#include <iostream>

Enemy::Enemy() : Character{ {0,0}, 40, 15, 5 }, m_nextAttack{ ESCAPE }, m_seqIndex{ 0 }, m_itemDropChance{0}
{
	m_priority = PRIORITY_ENEMY;
}

Enemy::Enemy(Point2D pos, int HP, int AT, int DF, String name, float chance) :
	Character{ pos, HP, AT, DF }, m_name{ name }, m_nextAttack{ESCAPE}, m_seqIndex{ 0 }, m_itemDropChance{chance}
{
	m_priority = PRIORITY_ENEMY;
}

Enemy::~Enemy()
{

}

int Enemy::OnAttacked(int damageDealt)
{
	int damage = damageDealt - m_defendPoints;
	if (damage <= 0) damage = rand() % 10 + 1; // if DF was too high, take small random dmg

	m_healthPoints -= damage;
	if (m_healthPoints < 0) m_healthPoints = 0;
	return damage;
}

int Enemy::Attack(Player* pPlayer)
{
	// Make sure a dead enemy doesn't attack!
	if (!IsAlive()) { return -1; }

	int damage = 0;
	// Act on attack intent
	switch (m_nextAttack)
	{
	case WEAK:
		// deal low amount of damage
		damage = m_attackPoints * 0.75f + (rand() % 4) - 2 - pPlayer->GetDF();
		if (damage <= 0) damage = rand() % 5 + 1; // if DF was too high, deal small random dmg
		// print result of attack
		std::cout << INDENT << "The enemy hit you with a weak attack, dealing " 
			<< RED << damage << " damage. " << RESET_COLOR << std::endl
			<< INDENT << "You have " << pPlayer->GetHP() - damage << "HP remaining." << std::endl;
		break;
	case MED:
		// deal normal amount of damage
		damage = m_attackPoints + (rand() % 4) - 2 - pPlayer->GetDF();
		if (damage <= 0) damage = rand() % 5 + 1; // if DF was too high, deal small random dmg
		// print result of attack
		std::cout << INDENT << "The enemy hit you with a normal attack, dealing "
			<< RED << damage << " damage. " << RESET_COLOR << std::endl
			<< INDENT << "You have " << pPlayer->GetHP() - damage << "HP remaining." << std::endl;
		break;
	case STRONG:
		// deal high amount of damage
		damage = m_attackPoints * 2 + (rand() % 4) - 2 - pPlayer->GetDF();
		if (damage <= 0) damage = rand() % 5 + 1; // if DF was too high, deal small random dmg
		std::cout << INDENT << "The enemy hit you with a strong attack, dealing "
			<< RED << damage << " damage. " << RESET_COLOR << std::endl
			<< INDENT << "You have " << pPlayer->GetHP() - damage << "HP remaining." << std::endl;
		break;
	case DEBUFF:
		damage = -1;
		break;
	case STEAL:
		damage = -1;
		break;
	case ESCAPE:
		damage = -1;
		break;
	default:
		damage = -1;
		break;
	}

	// Switch intent to the next attack in the sequence
	m_seqIndex = (m_seqIndex + 1) % m_attackSequence.size();
	m_nextAttack = m_attackSequence[m_seqIndex];

	return damage;
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

