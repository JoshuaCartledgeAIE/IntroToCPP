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

	float GetMana() { return m_manaPoints; }

	void Draw() override;
	void DrawDescription() override;
	void LookAt() override;

	void LearnSpell(String spellName);

	void ExecuteCommand(int command, Room* pRoom, String spellName, Game* game);

private:
	void Pickup(Room* pRoom);
	void Attack(Enemy* pEnemy);
	void CastSpell(String spellName, Game* game);

private:

	float m_manaPoints;

	float m_maxHP = 100.0f;
	float m_maxMP = 80.0f;
	const int BASE_AT = 20;
	const int BASE_DF = 5;

	std::vector<Spell*> m_spells;
};

