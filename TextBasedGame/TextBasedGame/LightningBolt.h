#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

class LightningBolt : public Spell
{
public:
	LightningBolt();

	void Cast(Game* game, Player* pPlayer) override;
};

