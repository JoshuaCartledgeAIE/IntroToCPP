#include "Character.h"
#include "Item.h"
#include <algorithm>

Character::Character() : GameObject{{0,0}}, m_healthPoints{0}, m_attackPoints{0},
m_defendPoints{0}
{
}

Character::Character(Point2D pos, float HP, float AT, float DF) :GameObject{ pos },
m_healthPoints{ HP }, m_attackPoints{ AT }, m_defendPoints{ DF }
{
}
