#pragma once
#include "GameDefines.h"

class Room;
class Player;
class Game;

class Spell
{
public:
	Spell();
	Spell(int cost, String name, bool forCombat, String desc);

	virtual void Cast(Game* game, Player* pPlayer) = 0;

	String GetName() { return m_name; }
	String GetDescription() { return m_description; }
	int GetCost() { return m_manaCost; }

	bool IsForCombat() { return m_forCombat; }
	static bool Compare(Spell* s1, Spell* s2) { return s1->m_name < s2->m_name; }

protected:

	int m_manaCost;
	String m_name;
	bool m_forCombat;
	String m_description;
};

