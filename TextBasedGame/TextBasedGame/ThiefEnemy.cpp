#include "ThiefEnemy.h"
#include <iostream>

ThiefEnemy::ThiefEnemy() : Enemy{ {0, 0}, 50, 12, 8, String(""), 0.8f }
{
	// Pick a random name for this enemy
	String names[] = { "Rat", "Bandit", "Poltergeist" };
	m_name = names[rand() % 3];

	// Pick a random attack sequence for this enemy
	std::vector<std::vector<EnemyAttack>> sequences =
		{ {STEAL, STEAL, ESCAPE}, {STEAL, MED, ESCAPE, },
		{STRONG, STEAL, ESCAPE}, {STEAL, ESCAPE} };
	m_attackSequence = sequences[rand() % sequences.size()];
	m_nextAttack = m_attackSequence[0];

	// Randomise all stats slightly
	m_healthPoints = m_healthPoints + rand() % 15 - 10;
	m_attackPoints = m_attackPoints + rand() % 5 - 2;
	m_defendPoints = m_defendPoints + rand() % 3 - 1;
}

void ThiefEnemy::Draw()
{
	std::cout << "[" << ORANGE << "\x8B" << RESET_COLOR << "]  ";
}
