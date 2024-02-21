#include "Spell.h"

Spell::Spell() : m_manaCost{0}, m_name{String("Empty")}, m_forCombat{false}, m_description{String("Hey you forgot to initialise the spell correctly, dummy!")}
{

}

Spell::Spell(int cost, String name, bool forCombat, String desc) : m_manaCost{ cost },
m_name{ name }, m_forCombat{ forCombat }, m_description{desc}
{
}

Spell::~Spell()
{
}
