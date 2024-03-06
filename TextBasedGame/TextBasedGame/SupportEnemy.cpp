#include "SupportEnemy.h"

SupportEnemy::SupportEnemy() : Enemy{ {0,0}, 35, 10, 5, String(""), 0.5f }
{
	// Pick a random name for this enemy
	String names[] = { "Orc Wizard", "Goblin Shaman" };
	m_name = names[rand() % 2];

	// Pick a random attack sequence for this enemy
	std::vector<std::vector<EnemyAttack>> sequences =
	{ {DEBUFF, MED, HEAL}, {WEAK, HEAL, MED},
	{MED, DEBUFF, HEAL}};
	m_attackSequence = sequences[rand() % sequences.size()];
	m_nextAttack = m_attackSequence[0];

	// Randomise all stats slightly
	m_healthPoints = m_healthPoints + rand() % 15 - 10;
	m_attackPoints = m_attackPoints + rand() % 5 - 2;
	m_defendPoints = m_defendPoints + rand() % 3 - 1;
}

void SupportEnemy::Draw()
{
	std::cout << "[" << RED << "\x94" << RESET_COLOR << "]  ";
}
