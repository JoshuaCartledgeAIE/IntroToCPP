#pragma once
#include "Item.h"
#include "Player.h"

class SpellcastingGuidebook : public Item
{
public:
	SpellcastingGuidebook();

	void OnPickup(Player* pPlayer) override;
};

class Torch : public Item 
{
public:
	Torch();

	void OnPickup(Player* pPlayer) override;
};

class LuckyClover : public Item
{
public:
	LuckyClover();

	void OnPickup(Player* pPlayer) override;
};

class HarvestersScythe : public Item
{
public:
	HarvestersScythe();

	void OnPickup(Player* pPlayer) override;
};

