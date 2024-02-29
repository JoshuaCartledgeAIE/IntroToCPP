#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class Teleport : public Spell
{
public:
	Teleport();

	void Cast(Game* game, Player* pPlayer) override;

private:


};

