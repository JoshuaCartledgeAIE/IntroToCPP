#include "Spellbook.h"
#include <iostream>

Spellbook::Spellbook() : m_spellToLearn{String(" ")}, Item{ String("Spellbook"), String("") }
{
}

Spellbook::Spellbook(String spell) : m_spellToLearn{spell}
{
	m_name = spell + String(" Spellbook");
}

Spellbook::~Spellbook()
{
}

void Spellbook::OnPickup(Player* pPlayer)
{
	// Make player learn the spell
	pPlayer->LearnSpell(m_spellToLearn);
	std::cout << INDENT << "The spellbook teaches you how to cast " << MAGENTA << m_spellToLearn << RESET_COLOR << "!" << std::endl;
}
