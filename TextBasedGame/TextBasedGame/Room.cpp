#include "Room.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "Item.h"
#include "Player.h"
#include "String.h"
#include "GameObject.h"
#include "Enemy.h"
#include <algorithm>

Room::Room() : m_mapPosition{0, 0}, m_type{EMPTY}
{
}

Room::~Room()
{

}

void Room::SetPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::AddGameObject(GameObject* object)
{
	// Add object to the room and sort objects by priority
	m_objects.push_back(object);
	std::sort(m_objects.begin(), m_objects.end(), GameObject::Compare);
}

void Room::RemoveGameObject(GameObject* object)
{
	// loop through objects in room until target object is found, then remove it
	for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
		if (*it == object) {
			m_objects.erase(it);
			return;
		}
	}
}

void Room::Draw()
{
	// find the console output position
	Point2D outPos = { INDENT_X + (5 * m_mapPosition.x) + 1,  MAP_Y + (m_mapPosition.y * 2) };
	// jump to the correct location
	std::cout << CSI << outPos.y << ";" << outPos.x << "H" << RESET_COLOR;
	
	// draw the room based on its type/contents
	switch (m_type) {
	case EMPTY:
		if (m_objects.size() > 0) {
			m_objects[0]->Draw();
		}
		else {
			// empty room
			std::cout << "[" << GREEN << "\xb0" << RESET_COLOR << "]  ";
		}
		break;
	case ENTRANCE:
		// entrance
		std::cout << "[" << WHITE << "\x9d" << RESET_COLOR << "]  ";
		break;
	case EXIT:
		// exit
		std::cout << "[" << WHITE << "\xFE" << RESET_COLOR << "]  ";
		break;
	}

	// draw room transitions
	for (int dir : m_transitions) {
		switch (dir)
		{
			// jump to the correct location and print the correct transition char
		case NORTH:
			std::cout << CSI << outPos.y - 1 << ";" << outPos.x + 1 << "H" << RESET_COLOR;
			std::cout << "|";
			break;
		case SOUTH:
			std::cout << CSI << outPos.y + 1 << ";" << outPos.x + 1 << "H" << RESET_COLOR;
			std::cout << "|";
			break;
		case EAST:
			std::cout << CSI << outPos.y << ";" << outPos.x + 3 << "H" << RESET_COLOR;
			std::cout << "\xC4\xC4";
			break;
		case WEST:
			std::cout << CSI << outPos.y << ";" << outPos.x - 2 << "H" << RESET_COLOR;
			std::cout << "\xC4\xC4";
			break;
		default:
			break;
		}
	}
}

void Room::DrawDescription()
{
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	// Delete 1 line and insert 1 empty line
	std::cout << CSI << "1M" << CSI << "1L" << std::endl;
	// write description of current room
	switch (m_type) {
	case EMPTY:
		if (m_objects.size() > 0) {
			m_objects[0]->DrawDescription();
		}
		else {
			// empty room
			std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		}
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked.There is no going back." << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}

void Room::LookAt()
{
	if (m_objects.size() > 0) {
		m_objects[0]->LookAt();
	}
	else {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << std::endl;
	}
}

Enemy* Room::GetEnemy()
{
	for (GameObject* obj : m_objects) {
		Enemy* enemy = dynamic_cast<Enemy*>(obj);
		if (enemy != nullptr)
			return enemy;
	}
	return nullptr;
}

Item* Room::GetItem()
{
	for (GameObject* obj : m_objects) {
		Item* item = dynamic_cast<Item*>(obj);
		if (item != nullptr)
			return item;
	}
	return nullptr;
}

void Room::RandomiseTransitions(Room** map)
{
	int tCount = rand() % 2 + 1; // add random number of transitions between 2 and 4
	int emergencyExit = 0;
	while (m_transitions.size() < tCount) {
		int dirToAdd = (rand() % 4 + 1) * 2;
		// Check if transition is already in the vector before adding
		if (std::find(m_transitions.begin(), m_transitions.end(), dirToAdd) == m_transitions.end()) {
			AddTransition(dirToAdd, map, true);
		}
		emergencyExit++;
		if (emergencyExit > 100) break;
	}

}

/// <summary>
/// PASSING MAP THROUGH TO HERE HAS A LOT OF PROBLEMS RIGHT NOW, NEED TO FIX LATER!!!
/// </summary>
/// <param name="tranDir"></param>
/// <param name="map"></param>
/// <param name="addInverse"></param>

void Room::AddTransition(int tranDir, Room** map, bool addInverse)
{
	// Check if on edge and transition is trying to go toward edge
	if (tranDir == NORTH && m_mapPosition.y == 0)
		return;
	if (tranDir == SOUTH && m_mapPosition.y == MAZE_HEIGHT - 1)
		return;
	if (tranDir == WEST && m_mapPosition.x == 0)
		return;
	if (tranDir == EAST && m_mapPosition.x == MAZE_WIDTH - 1)
		return;

	// Add transition to this room
	m_transitions.push_back(tranDir);
	std::sort(m_transitions.begin(), m_transitions.end());

	// Add the same transition in reverse to the adjoining room
	switch (tranDir) {
	case NORTH:
		map[m_mapPosition.y - 1][m_mapPosition.x].AddTransition(SOUTH, map, false);
		break;
	case SOUTH:
		map[m_mapPosition.y + 1][m_mapPosition.x].AddTransition(NORTH, map, false);
		break;
	case EAST:
		map[m_mapPosition.y][m_mapPosition.x + 1].AddTransition(WEST, map, false);
		break;
	case WEST:
		map[m_mapPosition.y][m_mapPosition.x - 1].AddTransition(EAST, map, false);
		break;
	}
}
