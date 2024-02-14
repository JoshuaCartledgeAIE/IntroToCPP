#pragma once
#include "String.h"

class Powerup
{
public:
	Powerup(String name, float health, float attack, float defence);
	~Powerup();

	String getName();
	float getHealthMultiplier();
	float getAttackMultiplier();
	float getDefenceMultiplier();

	static bool Compare(Powerup& p1, Powerup& p2);

private:
	String m_name;
	
	float m_healthMultiplier;
	float m_attackMultiplier;
	float m_defenceMultiplier;
};

