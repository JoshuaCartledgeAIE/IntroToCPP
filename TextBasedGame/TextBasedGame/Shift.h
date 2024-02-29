#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class Shift : public Spell
{
public:
	Shift();

	void Cast(Game* game, Player* pPlayer) override;

private:


};

