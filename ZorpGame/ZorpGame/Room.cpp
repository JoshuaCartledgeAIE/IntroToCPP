#include "Room.h"
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
	Point2D outPos = { INDENT_X + (6 * m_mapPosition.x) + 1,  MAP_Y + m_mapPosition.y };
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
			std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		}
		break;
	case ENTRANCE:
		// entrance
		std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
		break;
	case EXIT:
		// exit
		std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
		break;
	}
}

void Room::DrawDescription()
{
	// reset draw colors
	std::cout << RESET_COLOR;
	// jump to the correct location
	std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	// Delete 4 lines and insert 4 empty lines
	std::cout << CSI << "4M" << CSI << "4L" << std::endl;
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
	for (GameObject* obj : m_objects) 
	{
		Item* item = dynamic_cast<Item*>(obj);
		if (item != nullptr)
			return item;
	}
	return nullptr;
}