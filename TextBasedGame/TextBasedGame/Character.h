#pragma once
#include "GameDefines.h"
#include "GameObject.h"
#include <vector>

class Item;

class Character : public GameObject
{
public:
	Character();
	Character(Point2D pos, float HP, float AT, float DF);
	~Character();

	virtual void Draw() = 0;
	virtual void DrawDescription() = 0;
	virtual void LookAt() = 0;

	float GetHP() { return m_healthPoints; }
	float GetAT() { return m_attackPoints; }
	float GetDF() { return m_defendPoints; }
	
	bool IsAlive() { return m_healthPoints > 0; }

	void AddItem(Item* pUp);

protected:
	std::vector<Item*> m_Items;

	float m_healthPoints;
	float m_attackPoints;
	float m_defendPoints;
};

