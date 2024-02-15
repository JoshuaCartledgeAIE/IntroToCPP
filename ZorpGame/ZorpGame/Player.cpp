#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "String.h"
#include "Food.h"
#include "Enemy.h"
#include <algorithm>
#include "Room.h"
#include "Character.h"

Player::Player() : Character{{0,0}, m_maxHP, BASE_AT, BASE_DF}
{
	m_healthPoints = m_maxHP;
	m_attackPoints = BASE_AT;
	m_defendPoints = BASE_DF;
	m_priority = PRIORITY_PLAYER;
}

Player::Player(Point2D position) : Character{ position, m_maxHP, BASE_AT, BASE_DF }
{
	m_healthPoints = m_maxHP;
	m_attackPoints = BASE_AT;
	m_defendPoints = BASE_DF;
	m_priority = PRIORITY_PLAYER;
}

Player::~Player()
{
	for (auto iter = m_powerups.begin(); iter < m_powerups.end(); iter++) {
		delete (*iter);
	}
	m_powerups.clear();
}

void Player::AddPowerup(Powerup* pUp)
{
	// Add new powerup to the array and sort it alphabetically
	m_powerups.push_back(pUp);
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::Compare);

	// Apply the stat buffs from the powerup
	float healthChange = m_maxHP * pUp->GetHealthMultiplier() - m_maxHP;
	m_healthPoints += healthChange;
	m_maxHP *= pUp->GetHealthMultiplier();

	m_attackPoints *= pUp->GetAttackMultiplier();

	m_defendPoints *= pUp->GetDefenceMultiplier();
}

void Player::Draw()
{
	Point2D outPos = { INDENT_X + (6 * m_mapPosition.x) + 3,  MAP_Y + m_mapPosition.y };
	// draw the player's position on the map
	// move cursor to map pos and delete character at current position
	std::cout << CSI << outPos.y << ";" << outPos.x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;

	// Draw inventory
	std::cout << INVENTORY_OUTPUT_POS << CSI << "4M";
	std::cout << INVENTORY_OUTPUT_POS <<"Inventory: ";
	for (auto iter = m_powerups.begin(); iter < m_powerups.end(); iter++) {
		std::cout << (*iter)->GetName() << "\t";
	}
	std::cout << std::endl << INDENT << "HP: " << (int)m_healthPoints << "/" << (int)m_maxHP
		<< "    Attack: " << (int)m_attackPoints << "     Defense: " << (int)m_defendPoints;
}

void Player::DrawDescription()
{
}

void Player::LookAt()
{
}

void Player::ExecuteCommand(int command, Room* pRoom)
{
	switch (command) {
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1) {
			m_mapPosition.x++;
		}
		return;
	case WEST:
		if (m_mapPosition.x > 0) {
			m_mapPosition.x--;
		}
		return;
	case NORTH:
		if (m_mapPosition.y > 0) {
			m_mapPosition.y--;
		}
		return;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1) {
			m_mapPosition.y++;
		}
		return;
	case LOOK:
		pRoom->LookAt();
		break;
	case FIGHT:
		Attack(pRoom->GetEnemy());
		break;
	case PICKUP:
		Pickup(pRoom);
		break;
	default:
		// the command was not valid so do nothing
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;
		break;
	}

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

void Player::Pickup(Room* pRoom)
{
	// check if powerup exists in room
	if (pRoom->GetPowerup() != nullptr) {
		Powerup* powerup = pRoom->GetPowerup();

		// Tell user what powerup was picked up
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You picked up the " << powerup->GetName() << std::endl;

		// add powerup to inventory
		AddPowerup(powerup);

		// Clear powerup from room
		pRoom->RemoveGameObject(powerup);
	}
	// check if food exists in room
	else if (pRoom->GetFood() != nullptr) {
		Food* food = pRoom->GetFood();

		// Eat the food and increase health
		m_healthPoints += food->GetHP();
		if (m_healthPoints > m_maxHP) m_healthPoints = m_maxHP;

		// Tell user that they ate food, and their new resulting health
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You eat the tasty food. Your health is now " << m_healthPoints << std::endl;

		// Clear food from room
		pRoom->RemoveGameObject(food);
	}
	else {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
	}
}

void Player::Attack(Enemy* pEnemy)
{
	if (pEnemy == nullptr) {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here to fight." << std::endl;
	}
	else {

		// Tell enemy to take damage from the attack
		pEnemy->OnAttacked(m_attackPoints);

		// If enemy dies, tell the player
		if (pEnemy->IsAlive() == false) {
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight the grue and kill it!" << std::endl;
		}
		else {
			// Otherwise the enemy fights back
			int damage = pEnemy->GetAT() - m_defendPoints;
			if (damage < 0) damage = 1 + rand() % 10;
			m_healthPoints -= damage;

			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
				"You fight a grue and take " << damage <<
				" points damage. Your health is now at " << m_healthPoints <<
				std::endl;
			std::cout << INDENT << "The grue has " << pEnemy->GetHP() <<
				" health remaining." << std::endl;
		}
	}
}


