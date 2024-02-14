#include "Room.h"
#include "GameDefines.h"
#include <iostream>
#include "Point2D.h"
#include "Powerup.h"
#include "Player.h"
#include "String.h"



Room::Room() : m_mapPosition{0, 0}, m_type{0}, m_powerup{nullptr}
{
}

Room::~Room()
{
	if (m_powerup != nullptr) delete m_powerup;
}

void Room::SetPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::SetType(int type)
{
	m_type = type;

	// If it is not a treasure room, then abort early
	if (!(type >= TREASURE_HP && type <= TREASURE_DF && m_powerup == nullptr)) {
		return;
	}
	
	// Otherwise, add a powerup to the room
	String name = "";

	float HP = 1;
	float AT = 1;
	float DF = 1;

	// Choose type of item based on room type
	switch (type) {
	case TREASURE_HP:
		name = "potion of ";
		HP = 1.1f;
		break;
	case TREASURE_AT:
		name = "sword of ";
		AT = 1.1f;
		break;
	case TREASURE_DF:
		name = "shield of ";
		DF = 1.1f;
		break;
	}

	// Pick random adjective modifier
	int item = rand() % 15;
	name.Append(itemNames[item]);
	m_powerup = new Powerup(name, HP, AT, DF);
}

int Room::GetType()
{
	return m_type;
}

void Room::Draw()
{
	// find the console output position
	Point2D outPos = { INDENT_X + (6 * m_mapPosition.x) + 1,  MAP_Y + m_mapPosition.y };
	// jump to the correct location
	std::cout << CSI << outPos.y << ";" << outPos.x << "H" << RESET_COLOR;
	// draw the room
	switch (m_type) {
	case EMPTY:
		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		break;
	case ENEMY:
		std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
		break;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
		std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
		break;
	case FOOD:
		std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
		break;
	case ENTRANCE:
		std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
		break;
	case EXIT:
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
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENEMY:
		std::cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching." << std::endl;
		break;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
		std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << std::endl;
		break;
	case FOOD:
		std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked.There is no going back." << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}

bool Room::ExecuteCommand(int command, Player* pPlayer)
{
	// position cursor correctly
	std::cout << EXTRA_OUTPUT_POS;

	switch(command){
	case LOOK:
		// Display different message if there is treasure present
		if (m_type >= TREASURE_HP && m_type <= TREASURE_DF) {
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enough to pick up." << std::endl;
		}
		else {
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning." << std::endl;
		}
		
		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		return true;
	case FIGHT:
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon." << std::endl;
		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		return true; 
	case PICKUP:
		return Pickup(pPlayer);
	default:
		// the direction was not valid,
		// do nothing, go back to the top of the loop and ask again
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it." << std::endl;
		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		break;
	}
	return false;
}

bool Room::Pickup(Player* pPlayer)
{
	// If it is not a treasure room or it is empty, then this fails
	if (!(m_type >= TREASURE_HP && m_type <= TREASURE_DF) || m_powerup == nullptr) {
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
		return true;
	}
	
	// Add the powerup to the player's inventory
	pPlayer->AddPowerup(m_powerup);

	// Remove the powerup from this room
	m_powerup = nullptr;

	// Change room type to Empty
	m_type = EMPTY;

	return true;
}
