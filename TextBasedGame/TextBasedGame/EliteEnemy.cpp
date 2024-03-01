#include "EliteEnemy.h"

EliteEnemy::EliteEnemy() : Enemy{{0,0}, 60, 20, 10, String(" "), 1.0f}
{
	// Pick a random name for this enemy
	String names[] = { "Ogre", "Golem", "Troll" };
	m_name = names[rand() % 3];

	// Pick a random attack sequence for this enemy
	std::vector<std::vector<EnemyAttack>> sequences =
	{ {STRONG, WEAK, STRONG}, {WEAK, STRONG, STRONG, STRONG},
	{MED, MED, STRONG}};
	m_attackSequence = sequences[rand() % sequences.size()];
	m_nextAttack = m_attackSequence[0];

	// Randomise all stats slightly
	m_healthPoints = m_healthPoints + rand() % 15 - 10;
	m_attackPoints = m_attackPoints + rand() % 5 - 2;
	m_defendPoints = m_defendPoints + rand() % 3 - 1;
}

void EliteEnemy::Draw()
{
	std::cout << "[" << DARK_RED << "\x99" << RESET_COLOR << "]  ";
}
