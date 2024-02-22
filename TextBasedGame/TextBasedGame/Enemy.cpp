#include "Enemy.h"
#include "Character.h"
#include <iostream>

Enemy::Enemy() : Character{ {0,0}, 40, 15, 5 }
{
	m_priority = PRIORITY_ENEMY;
}

void Enemy::OnAttacked(int attackPoints)
{
	int damage = attackPoints - m_defendPoints;
	if (damage < 0) damage = 0;

	m_healthPoints -= damage;
	if (m_healthPoints < 0) m_healthPoints = 0;
}

void Enemy::Draw()
{
	std::cout << "[" << RED << "\x94" << RESET_COLOR << "]  ";
}

void Enemy::DrawDescription()
{
	std::cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching." << std::endl;
}

