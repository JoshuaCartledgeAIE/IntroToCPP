#include "BasicEnemy.h"
#include <iostream>

BasicEnemy::BasicEnemy() : Enemy{{0,0}, 40, 15, 5, String("")}
{
	// Pick a random name for this enemy
	String names[] = { "Bat", "Slime", "Skeleton" };
	m_name = names[rand() % 3];

	// Pick a random attack sequence for this enemy
	std::vector<EnemyAttack> sequences[3] = { {WEAK, STRONG, WEAK}, {MED, MED, STRONG} };
	m_attackSequence = sequences[rand() % 2];
	m_nextAttack = m_attackSequence[0];
}

BasicEnemy::~BasicEnemy()
{
}
void BasicEnemy::Draw()
{
	std::cout << "[" << RED << "\x94" << RESET_COLOR << "]  ";
}
