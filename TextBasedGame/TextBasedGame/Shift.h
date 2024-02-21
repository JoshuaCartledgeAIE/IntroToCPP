#pragma once
#include "Spell.h"
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class Shift : public Spell
{
public:
	Shift();
	~Shift();

	bool Cast(Game* game, Player* pPlayer) override;

private:


};

