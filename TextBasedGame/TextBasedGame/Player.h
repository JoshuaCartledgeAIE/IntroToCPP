#pragma once
#include "Point2D.h"
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

	void AddItem(Item* pUp);

	void SetPosition(const Point2D& position) { m_mapPosition = position;}
	Point2D GetPosition() { return m_mapPosition; };

	float GetAT() { return m_attackPoints; }
	float GetDF() { return m_defendPoints; }
	float GetHP() { return m_healthPoints; }
	float GetMaxHP() { return m_maxHP; }
	float GetMP() { return m_manaPoints; }
	float GetMaxMP() { return m_maxMP; }

	void SetMaxMP(int value) { m_maxMP = value;}
	void SetMaxHP(int value) { m_maxHP = value;}
	void SetMP(int value) { m_manaPoints = value;}
	void SetHP(int value) { m_healthPoints = value; }
	void SetAT(int value) { m_attackPoints = value; }
	void SetDF(int value) { m_defendPoints = value; }

	bool IsInCombat() { return m_inCombat; }
	void SetCombatState(bool combat) { m_inCombat = combat; }

	void Draw() override;
	void DrawDescription() override;

	void LearnSpell(String spellName);

	void ExecuteCommand(int command, Room* pRoom, String spellName, Game* game);

private:
	void Pickup(Room* pRoom);
	void Attack(Enemy* pEnemy, Game* game, bool isRisky);
	void CastSpell(String spellName, Game* game);

private:

	float m_manaPoints;

	float m_maxHP = 100.0f;
	float m_maxMP = 80.0f;

	std::vector<Spell*> m_spells;

	bool m_inCombat;
};

