#include "StatBooster.h"
#include <iostream>

StatBooster::StatBooster()
{
}

StatBooster::StatBooster(int amount, StatType type) : m_statBoostAmount{amount}, m_statBoostType{type}
{
	int shoddyThreshold = 0;
	int ordinaryThreshold = 0;

	switch (m_statBoostType) 
	{
	case HP:
		// Give name and description according to stat type
		m_name = String(" Health Crystal");
		m_description = String("Raises Max HP.");
		shoddyThreshold = 13;
		ordinaryThreshold = 16;
		break;
	case MP:
		// Give name and description according to stat type
		m_name = String(" Mana Crystal");
		m_description = String("Raises Max MP.");
		shoddyThreshold = 11;
		ordinaryThreshold = 14;
		break;
	case AT:
		// Give name and description according to stat type
		m_name = String(" Sword");
		m_description = String("Raises Attack.");
		shoddyThreshold = 5;
		ordinaryThreshold = 7;
		break;
	case DF:
		// Give name and description according to stat type
		m_name = String(" Shield");
		m_description = String("Raises Defense.");
		shoddyThreshold = 4;
		ordinaryThreshold = 6;
		break;
	default:
		m_name = String("Bad statType!");
		m_description = String("You messed up big time!");
		break;
	}

	// Give prefix according to magnitude of stat boost
	if (amount < shoddyThreshold)
		m_name.Prepend("Shoddy");
	else if (amount < ordinaryThreshold)
		m_name.Prepend("Ordinary");
	else
		m_name.Prepend("Superior");
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
		std::cout << GREEN << "max HP " << RESET_COLOR;
		break;
	case MP:
		pPlayer->SetMaxMP(pPlayer->GetMaxMP() + m_statBoostAmount);
		pPlayer->SetMP(pPlayer->GetMP() + m_statBoostAmount);
		std::cout << BLUE << "max MP " << RESET_COLOR;
		break;
	case AT:
		pPlayer->SetAT(pPlayer->GetAT() + m_statBoostAmount);
		std::cout << YELLOW << "attack " << RESET_COLOR;
		break;
	case DF:
		pPlayer->SetDF(pPlayer->GetDF() + m_statBoostAmount);
		std::cout << YELLOW << "defense " << RESET_COLOR;
		break;
	default:
		std::cout << "Oopsie! ";
		break;
	}

	std::cout << "has been raised by " << YELLOW << m_statBoostAmount 
		 << " points." << RESET_COLOR << std::endl;

	pPlayer->Draw();
}
