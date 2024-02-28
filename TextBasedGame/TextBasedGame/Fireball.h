#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"

class Fireball : public Spell
{
public:
	Fireball();
	~Fireball();

	void Cast(Game* game, Player* pPlayer) override;
};

