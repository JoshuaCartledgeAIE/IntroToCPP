#include "SimpleItems.h"
#include <iostream>

SpellcastingGuidebook::SpellcastingGuidebook()
{
	m_name = String("Spellcasting Guidebook");
	m_description = String("Reduces the mana cost of all spells by 25%.");
}

void SpellcastingGuidebook::OnPickup(Player* pPlayer)
{
	std::cout << INDENT << "The mana cost of all spells you cast is now reduced by 25%!" << std::endl;
	pPlayer->m_spellCostMultiplier = 0.75f;
}

void SpellcastingGuidebook::OnStolen(Player* pPlayer)
{
	pPlayer->m_spellCostMultiplier = 1.0f;
}

Torch::Torch()
{
	m_name = String("Torch");
	m_description = String("Increases your vision range to 2 rooms away.");
}

void Torch::OnPickup(Player* pPlayer)
{
	std::cout << INDENT << "Your vision range now extends to 2 rooms away!" << std::endl;
	pPlayer->m_visionRange = 2;
}

void Torch::OnStolen(Player* pPlayer)
{
	pPlayer->m_visionRange = 1;
}

LuckyClover::LuckyClover()
{
	m_name = String("Lucky Clover");
	m_description = String("Increases your hit chance to 75% when performing a risky attack.");
}

void LuckyClover::OnPickup(Player* pPlayer)
{
	std::cout << INDENT << "You now have a increased chance to hit your risky attacks!" << std::endl;
	pPlayer->m_riskyHitChance = 0.75f;
}

void LuckyClover::OnStolen(Player* pPlayer)
{
	pPlayer->m_riskyHitChance = 0.5f;
}

HarvestersScythe::HarvestersScythe()
{
	m_name = String("Harvester's Scythe");
	m_description = String("Gain a small amount of HP when you kill an enemy.");
}

void HarvestersScythe::OnPickup(Player* pPlayer)
{
	std::cout << INDENT << "You now gain a small amount of HP each time you kill an enemy!" << std::endl;
	pPlayer->m_gainHPOnKill = true;
}

void HarvestersScythe::OnStolen(Player* pPlayer)
{
	pPlayer->m_gainHPOnKill = false;
}
