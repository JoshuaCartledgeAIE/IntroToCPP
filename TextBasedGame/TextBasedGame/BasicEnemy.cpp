#include "BasicEnemy.h"
#include <iostream>

BasicEnemy::BasicEnemy() : Enemy{{0,0}, 40, 15, 5, String(""), 50}
{
	// Pick a random name for this enemy
	String names[] = { "Bat", "Slime", "Skeleton" };
	m_name = names[rand() % 3];

	// Pick a random attack sequence for this enemy
	std::vector<std::vector<EnemyAttack>> sequences = 
		{ {WEAK, STRONG, WEAK}, {WEAK, WEAK, STRONG, STRONG}, 
		{MED, MED, STRONG}, {WEAK, MED, STRONG} };
	m_attackSequence = sequences[rand() % sequences.size()];
	m_nextAttack = m_attackSequence[0];

	// Randomise all stats slightly
	m_healthPoints = m_healthPoints + rand() % 15 - 10;
	m_attackPoints = m_attackPoints + rand() % 5 - 2;
	m_defendPoints = m_defendPoints + rand() % 3 - 1;
}

BasicEnemy::~BasicEnemy()
{
}
void BasicEnemy::Draw()
{
	std::cout << "[" << RED << "\x94" << RESET_COLOR << "]  ";
}
