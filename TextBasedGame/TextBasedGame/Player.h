#pragma once
#include "Character.h"
#include "Item.h"
#include "GameDefines.h"
#include <vector>
#include <algorithm>
#include "String.h"
#include "Enemy.h"
#include "Room.h"


class Item;
class Room;
class Enemy;
class Game;
class Spell;

class Player : public Character {
public:

	Player();
	Player(Point2D position);
	~Player();

	void AddItem(Item* item) override;

	void SetPosition(const Point2D& position) { m_mapPosition = position;}
	Point2D GetPosition() { return m_mapPosition; };

	float GetAT() { return m_attackPoints; }
	float GetDF() { return m_defendPoints; }
	float GetHP() { return m_healthPoints; }
	
	float GetMP() { return m_manaPoints; }
	float GetMaxMP() { return m_maxMP; }

	// Setters involving values with maximums should ensure that they stay under those maximums
	void SetMaxMP(float value) { m_maxMP = value; if (m_manaPoints > m_maxMP) m_manaPoints = m_maxMP;}
	
	void SetMP(float value) { m_manaPoints = value; if (m_manaPoints > m_maxMP) m_manaPoints = m_maxMP; }
	
	
	

	bool IsInCombat() { return m_inCombat; }
	void SetCombatState(bool combat) { m_inCombat = combat; }

	void Draw() override;
	void DrawDescription() override;

	void LearnSpell(String spellName);

	void ExecuteCommand(int command, Room* pRoom, String spellName, Game* game);

public:
	// variables that items interact with
	int m_visionRange = 1;
	float m_riskyHitChance = 0.5f;
	float m_spellCostMultiplier = 1.0f;
	bool m_gainHPOnKill = false;

private:
	void Pickup(Room* pRoom);
	void Attack(Enemy* pEnemy, Game* game, bool isRisky);
	void CastSpell(String spellName, Game* game);

private:

	float m_manaPoints;

	float m_maxMP = 80.0f;

	std::vector<Spell*> m_spells;

	bool m_inCombat;

	
};

