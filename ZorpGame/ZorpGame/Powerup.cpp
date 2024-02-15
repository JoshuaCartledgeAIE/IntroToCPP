#include "Powerup.h"
#include <iostream>
#include "String.h"
#include "GameDefines.h"

Powerup::Powerup() : m_healthMultiplier{1}, m_attackMultiplier{ 1 }, m_defenceMultiplier{ 1 }
{
	m_priority = PRIORITY_POWERUP;
	m_name[0] = 0;
}

Powerup::Powerup(String name, float health, float attack, float defence)
{
	m_name = name;
	m_priority = PRIORITY_POWERUP;
	m_healthMultiplier = health;
	m_attackMultiplier = attack;
	m_defenceMultiplier = defence;
}

Powerup::~Powerup()
{
}



bool Powerup::Compare(Powerup* p1, Powerup* p2)
{
	return p1->m_name < p2->m_name;
}

void Powerup::Draw()
{
	std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
}

void Powerup::DrawDescription()
{
	std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << std::endl;
}

void Powerup::LookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here.It looks small enough to pick up." << std::endl;
}
