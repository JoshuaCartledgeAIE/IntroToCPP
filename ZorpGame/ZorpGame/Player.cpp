#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "String.h"
#include <algorithm>

Player::Player() : m_mapPosition{0, 0}, m_healthPoints{100}, m_attackPoints{20}, m_defendPoints{20}
{
}

Player::Player(Point2D position) : m_mapPosition{position}, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{
}

Player::~Player()
{

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
		std::cout << iter->getName() << "\t";
	}
}

bool Player::ExecuteCommand(int command, int roomType)
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
	case PICKUP:
		return Pickup(roomType);
	}
	return false;
}

bool Player::Pickup(int roomType)
{
	static const char itemNames[15][30] = {
"indifference", "invisibility", "invulnerability", "incontinence",
"improbability", "impatience", "indecision", "inspiration",
"independence", "incurability", "integration", "invocation",
"inferno", "indigestion", "inoculation"
	};

	// pick arbitrary descriptive name for item
	int item = rand() % 15;
	String name = "";

	// pick random type for item
	switch (roomType) {
	case TREASURE_HP:
		name = "potion of ";
		break;
	case TREASURE_AT:
		name = "sword of ";
		break;
	case TREASURE_DF:
		name = "shield of ";
		break;
	default:
		return false;
	}

	name.Append(itemNames[item]);
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR <<
		"You pick up the " << name << std::endl;
	
	// Add item to player inventory
	m_powerups.push_back(Powerup(name, 1.0f, 1.0f, 1.1f));

	// Sort the player inventory
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::Compare);

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return true;
}
