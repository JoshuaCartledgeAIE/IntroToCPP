#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"

Player::Player() : m_mapPosition{0, 0} 
{
}

Player::Player(Point2D position) : m_mapPosition{position}
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
