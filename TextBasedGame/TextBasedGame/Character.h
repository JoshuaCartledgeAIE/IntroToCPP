#pragma once
#include "GameDefines.h"
#include "GameObject.h"
#include <vector>
#include "Item.h"
#include <algorithm>


class Item;

class Character : public GameObject
{
public:
	Character();
	Character(Point2D pos, float HP, float AT, float DF);
	~Character();

	virtual void Draw() = 0;
	virtual void DrawDescription() = 0;

	float GetMaxHP() { return m_maxHP; }
	float GetHP() { return m_healthPoints; }
	float GetAT() { return m_attackPoints; }
	float GetDF() { return m_defendPoints; }

	void SetMaxHP(float value);
	void SetHP(float value);
	void SetAT(float value) { m_attackPoints = value; }
	void SetDF(float value) { m_defendPoints = value; }
	
	bool IsAlive() { return m_healthPoints > 0; }

	virtual void AddItem(Item* item);

public:
	std::vector<Item*> m_inventory;

protected:
	
	float m_healthPoints;
	float m_maxHP;
	float m_attackPoints;
	float m_defendPoints;
};

