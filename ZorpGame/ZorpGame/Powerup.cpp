#include "Powerup.h"
#include <iostream>
#include "String.h"

Powerup::Powerup(String name, float health, float attack, float defence)
{
	m_name = name;
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
