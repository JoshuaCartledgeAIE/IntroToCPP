#include "Character.h"
#include "Item.h"
#include <algorithm>

Character::Character() : GameObject{ {0,0} }, m_maxHP{ 0 }, m_healthPoints { 0 }, m_attackPoints{ 0 },
m_defendPoints{0}
{
}

Character::Character(Point2D pos, float HP, float AT, float DF) :GameObject{ pos },
m_maxHP{ HP }, m_attackPoints{ AT }, m_defendPoints{ DF }
{
	m_healthPoints = m_maxHP;
}

Character::~Character()
{
	// clearing inventory here is a little irrelevant since all of the item pointers 
	// in the inventory are also held in the Game class and that already deletes them
	// but I'm doing it anyway just in case!
	for (auto iter = m_inventory.begin(); iter < m_inventory.end(); iter++) {
		delete (*iter);
	}
	m_inventory.clear();
}

void Character::SetMaxHP(float value) {
	m_maxHP = value;
	if (m_healthPoints > m_maxHP)
		m_healthPoints = m_maxHP;
	if (m_healthPoints < 0)
		m_healthPoints = 0;

}

void Character::SetHP(float value) {
	m_healthPoints = value;
	if (m_healthPoints > m_maxHP)
		m_healthPoints = m_maxHP;
	if (m_healthPoints < 0)
		m_healthPoints = 0;
}

void Character::AddItem(Item* item)
{
	m_inventory.push_back(item);
	std::sort(m_inventory.begin(), m_inventory.end(), Item::Compare);
}
