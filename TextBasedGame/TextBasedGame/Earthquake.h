#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include <iostream>

class Earthquake : public Spell
{
public:
	Earthquake();
	~Earthquake();

	void Cast(Game* game, Player* pPlayer) override;
};

