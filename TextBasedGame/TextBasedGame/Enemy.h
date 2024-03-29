#pragma once
#include "Character.h"
#include "GameDefines.h"
#include "Player.h"
#include "Item.h"

class Enemy : public Character
{
public:
	Enemy();
	Enemy(Point2D pos, int HP, int AT, int DF, String name, float chance);

	String GetName() { return m_name; }

	int OnAttacked(int damageDealt);
	void Attack(Player* pPlayer, Game* game);

	void OnDeath(Game* game);

	virtual void Draw() = 0;
	void DrawDescription() override;

protected:
	float CalculateDamage(float multiplier, Player* pPlayer);

protected:
	String m_name;
	EnemyAttack m_nextAttack;
	int m_seqIndex;
	std::vector<EnemyAttack> m_attackSequence;
	float m_itemDropChance;
};

