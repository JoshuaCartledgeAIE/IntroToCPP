#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

class Earthquake : public Spell
{
public:
	Earthquake();

	void Cast(Game* game, Player* pPlayer) override;
};

