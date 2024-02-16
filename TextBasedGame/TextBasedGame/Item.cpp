#include "Item.h"
#include <iostream>
#include "String.h"
#include "GameDefines.h"

Item::Item() : m_healthMultiplier{1}, m_attackMultiplier{ 1 }, m_defenceMultiplier{ 1 }
{
	m_priority = PRIORITY_Item;
	m_name[0] = 0;
}

Item::Item(String name, float health, float attack, float defence)
{
	m_name = name;
	m_priority = PRIORITY_Item;
	m_healthMultiplier = health;
	m_attackMultiplier = attack;
	m_defenceMultiplier = defence;
}

Item::~Item()
{
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
	std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << std::endl;
}

void Item::LookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here.It looks small enough to pick up." << std::endl;
}
