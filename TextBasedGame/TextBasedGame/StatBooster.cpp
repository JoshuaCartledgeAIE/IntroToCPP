#include "StatBooster.h"
#include <iostream>

StatBooster::StatBooster()
{
}

StatBooster::StatBooster(int amount, StatType type) : m_statBoostAmount{amount}, m_statBoostType{type}
{
	switch (m_statBoostType) 
	{
	case HP:
		// Give name and description according to stat type
		m_name = String(" Health Crystal");
		m_description = String("Raises Max HP.");
		break;
	case MP:
		// Give name and description according to stat type
		m_name = String(" Mana Crystal");
		m_description = String("Raises Max MP.");
		break;
	case AT:
		// Give name and description according to stat type
		m_name = String(" Sword");
		m_description = String("Raises Attack.");
		break;
	case DF:
		// Give name and description according to stat type
		m_name = String(" Shield");
		m_description = String("Raises Defense.");
		break;
	default:
		m_name = String("Bad statType!");
		m_description = String("You messed up big time!");
		break;
	}

	// Give prefix according to amount of stat boost
	if (amount < 8)
		m_name.Prepend("Shoddy");
	else if (amount < 14)
		m_name.Prepend("Ordinary");
	else
		m_name.Prepend("Superior");
}

StatBooster::~StatBooster()
{
}

void StatBooster::OnPickup(Player* pPlayer)
{
	std::cout << INDENT << "Your ";
	switch (m_statBoostType) // raise stat of the appropriate type
	{
	case HP:
		// when raising max HP or MP, also gain the same amount of HP or MP
		pPlayer->SetMaxHP(pPlayer->GetMaxHP() + m_statBoostAmount);
		pPlayer->SetHP(pPlayer->GetHP() + m_statBoostAmount);
		std::cout << "max HP";
		break;
	case MP:
		pPlayer->SetMaxMP(pPlayer->GetMaxMP() + m_statBoostAmount);
		pPlayer->SetMP(pPlayer->GetMP() + m_statBoostAmount);
		std::cout << "max MP ";
		break;
	case AT:
		pPlayer->SetAT(pPlayer->GetAT() + m_statBoostAmount);
		std::cout << "attack ";
		break;
	case DF:
		pPlayer->SetDF(pPlayer->GetDF() + m_statBoostAmount);
		std::cout << "attack ";
		std::cout << "defense ";
		break;
	default:
		std::cout << "Oopsie! ";
		break;
	}

	std::cout << "has been raised by " << m_statBoostAmount << " points." << std::endl;

	pPlayer->Draw();
}
