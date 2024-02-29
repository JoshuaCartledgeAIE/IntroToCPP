#include "Item.h"
#include <iostream>
#include "String.h"
#include "GameDefines.h"

Item::Item()
{
	m_priority = PRIORITY_ITEM;
	m_name = "default";
}

Item::Item(String name, String desc)
{
	m_name = name;
	m_name = desc;
	m_priority = PRIORITY_ITEM;
}


bool Item::Compare(Item* p1, Item* p2)
{
	return p1->m_name < p2->m_name;
}

void Item::Draw()
{
	std::cout << "[" << YELLOW << "$" << RESET_COLOR << "]  ";
}

void Item::DrawDescription()
{
	std::cout << INDENT << "There appears to be some " << YELLOW << 
		"treasure" << RESET_COLOR << " here. Use the 'pickup' command to grab it!" << std::endl;
}

