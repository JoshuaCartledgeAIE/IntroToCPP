#pragma once
#include "String.h"
#include "GameObject.h"

class Item : public GameObject
{
public:
	Item();
	Item(String name, float health, float attack, float defence);
	~Item();

	String GetName() { return m_name; }
	void SetName(String& str) { m_name = str; }

	float GetHealthMultiplier() { return m_healthMultiplier; }
	float GetAttackMultiplier() { return m_attackMultiplier; }
	float GetDefenceMultiplier() { return m_defenceMultiplier; }
	void SetHealthMultiplier(float value) { m_healthMultiplier = value; }
	void SetAttackMultiplier(float value) { m_attackMultiplier = value; }
	void SetDefenceMultiplier(float value) { m_defenceMultiplier = value; }

	static bool Compare(Item* p1, Item* p2);

	void Draw() override;
	void DrawDescription() override;

private:
	String m_name;
	
	float m_healthMultiplier;
	float m_attackMultiplier;
	float m_defenceMultiplier;
};

