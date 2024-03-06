#pragma once
#include "Item.h"
#include "GameDefines.h"
#include <vector>
#include "Character.h"
#include "Spell.h"

class Item;
class Room;
class Enemy;

class Player : public Character {
public:

	Player();
	Player(Point2D position);
	~Player();

	void AddItem(Item* item) override;

	void SetPosition(const Point2D& position) { m_mapPosition = position;}
	Point2D GetPosition() { return m_mapPosition; };

	float GetMP() { return m_manaPoints; }
	float GetMaxMP() { return m_maxMP; }

	float GetBlock(){ return m_block; }
	void SetBlock(float block) { m_block = block; }

	// Setters involving values with maximums should ensure that they stay under those maximums
	void SetMaxMP(float value) { m_maxMP = value; if (m_manaPoints > m_maxMP) m_manaPoints = m_maxMP;}
	void SetMP(float value) { m_manaPoints = value; if (m_manaPoints > m_maxMP) m_manaPoints = m_maxMP; }

	bool IsInCombat() { return m_inCombat; }
	void SetCombatState(bool combat) {
		m_inCombat = combat; if (!m_inCombat) m_debuffDamageMultiplier = 1.0f; // clear debuff at end of combat
	}

	void Draw() override;
	void DrawDescription() override;

	void LearnSpell(String spellName);

	void ExecuteCommand(int command, Room* pRoom, String spellName, int target, Game* game);

public:
	// variables that items interact with
	int m_visionRange = 1;
	float m_riskyHitChance = 0.5f;
	float m_spellCostMultiplier = 1.0f;
	bool m_gainHPOnKill = false;
	float m_debuffDamageMultiplier = 1.0f;

private:
	void Pickup(Room* pRoom);
	void Attack(std::vector<Enemy*> enemies, Game* game, bool isRisky);
	void CastSpell(String spellName, Game* game);

	Spell* SearchForSpell(String spellName);

private:

	float m_manaPoints;

	float m_maxMP = 80.0f;

	std::vector<Spell*> m_spells;

	bool m_inCombat;

	int m_block = 0;
};

