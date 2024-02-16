#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "String.h"

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
	for (auto iter = m_Items.begin(); iter < m_Items.end(); iter++) {
		delete (*iter);
	}
	m_Items.clear();
}

void Player::AddItem(Item* pUp)
{
	// Add new Item to the array and sort it alphabetically
	m_Items.push_back(pUp);
	std::sort(m_Items.begin(), m_Items.end(), Item::Compare);

	// Apply the stat buffs from the Item
	float healthChange = m_maxHP * pUp->GetHealthMultiplier() - m_maxHP;
	m_healthPoints += healthChange;
	m_maxHP *= pUp->GetHealthMultiplier();

	m_attackPoints *= pUp->GetAttackMultiplier();

	m_defendPoints *= pUp->GetDefenceMultiplier();
}

void Player::Draw()
{
	// Draw stats at top of screen
	std::cout << STATS_OUTPUT_POS << "HP: " << (int)m_healthPoints << "/" << (int)m_maxHP
		<< "    Attack: " << (int)m_attackPoints << "     Defense: " << (int)m_defendPoints;

	Point2D outPos = { INDENT_X + (5 * m_mapPosition.x) + 2,  MAP_Y + (m_mapPosition.y * 2) };
	// draw the player's position on the map
	// move cursor to map pos and delete character at current position, replace it with player
	std::cout << CSI << outPos.y << ";" << outPos.x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;

	// Draw inventory
	std::cout << INVENTORY_OUTPUT_POS << CSI << "4M";
	std::cout << INVENTORY_OUTPUT_POS <<"Inventory: ";
	for (auto iter = m_Items.begin(); iter < m_Items.end(); iter++) {
		std::cout << (*iter)->GetName() << "\t";
	}
	
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
	// check if Item exists in room
	if (pRoom->GetItem() != nullptr) {
		Item* Item = pRoom->GetItem();

		// Tell user what Item was picked up
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You picked up the " << Item->GetName() << std::endl;

		// add Item to inventory
		AddItem(Item);

		// Clear Item from room
		pRoom->RemoveGameObject(Item);
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


