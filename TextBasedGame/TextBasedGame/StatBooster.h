#pragma once
#include "Item.h"
#include "GameDefines.h"
#include "Player.h"

class StatBooster : public Item
{
public: 
	StatBooster();
	StatBooster(int amount, StatType type);

	void OnPickup(Player* pPlayer) override;
	void OnStolen(Player* pPlayer) override;

private:
	int m_statBoostAmount;
	StatType m_statBoostType;
};

