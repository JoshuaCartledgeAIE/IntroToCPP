#pragma once
#include "Point2D.h"
#include "Item.h"
#include "GameDefines.h"
#include <vector>
#include "Character.h"

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

	void Draw() override;
	void DrawDescription() override;
	void LookAt() override;


	void ExecuteCommand(int command, Room* pRoom);

private:
	void Pickup(Room* pRoom);
	void Attack(Enemy* pEnemy);

private:

	float m_maxHP = 100.0f;
	const int BASE_AT = 20;
	const int BASE_DF = 5;
};

