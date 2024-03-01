#pragma once
#include "Spell.h"
class IceShield : public Spell
{
public: 
    IceShield();

    void Cast(Game* game, Player* pPlayer) override;
};

