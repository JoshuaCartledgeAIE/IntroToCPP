#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

class Lightning : public Spell
{
public:
	Lightning();

	void Cast(Game* game, Player* pPlayer) override;
};

