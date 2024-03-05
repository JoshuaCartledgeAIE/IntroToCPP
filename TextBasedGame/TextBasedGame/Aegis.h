#pragma once
#include "Spell.h"
class Aegis : public Spell
{
public: 
    Aegis();

    void Cast(Game* game, Player* pPlayer) override;
};

