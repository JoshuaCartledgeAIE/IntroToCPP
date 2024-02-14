#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "String.h"
#include <algorithm>
#include "Room.h"

Player::Player() : m_mapPosition{0, 0}, m_healthPoints{100}, m_attackPoints{20}, m_defendPoints{20}
{
}

Player::Player(Point2D position) : m_mapPosition{position}, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{
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
}

void Player::SetPosition(Point2D position)
{
	m_mapPosition = position;
}

Point2D Player::GetPosition()
{
	return m_mapPosition;
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
}

bool Player::ExecuteCommand(int command)
{
	switch (command) {
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1) {
			m_mapPosition.x++;
		}
		return true;
	case WEST:
		if (m_mapPosition.x > 0) {
			m_mapPosition.x--;
		}
		return true;
	case NORTH:
		if (m_mapPosition.y > 0) {
			m_mapPosition.y--;
		}
		return true;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1) {
			m_mapPosition.y++;
		}
		return true;
	}

	return false;
}


