#include "Character.h"
#include "Powerup.h"
#include <algorithm>

Character::Character() : GameObject{{0,0}}, m_healthPoints{0}, m_attackPoints{0},
m_defendPoints{0}
{
}

Character::Character(Point2D pos, float HP, float AT, float DF) :GameObject{ pos },
m_healthPoints{ HP }, m_attackPoints{ AT }, m_defendPoints{ DF }
{
}

Character::~Character()
{
}

void Character::AddPowerup(Powerup* pUp)
{
	m_powerups.push_back(pUp);
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::Compare);
}
