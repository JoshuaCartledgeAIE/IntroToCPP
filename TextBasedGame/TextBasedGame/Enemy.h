#pragma once
#include "Point2D.h"
#include "Character.h"
#include "String.h"
#include "GameDefines.h"
#include "Player.h"

class Enemy : public Character
{
public:
	Enemy();
	Enemy(Point2D pos, int HP, int AT, int DF, String name);
	~Enemy();


	int OnAttacked(int damageDealt);
	int Attack(Player* pPlayer);

	virtual void Draw() = 0;
	void DrawDescription() override;

protected:
	String m_name;
	EnemyAttack m_nextAttack;
	int m_seqIndex;
	std::vector<EnemyAttack> m_attackSequence;
};

