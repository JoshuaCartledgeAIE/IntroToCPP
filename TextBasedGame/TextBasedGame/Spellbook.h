#pragma once
#include "Spell.h"
#include "Player.h"
#include "Item.h"

class Spellbook: public Item
{
public:
	Spellbook();
	Spellbook(String spell);

	void OnPickup(Player* pPlayer) override;

private:
	String m_spellToLearn;
};

