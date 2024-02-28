#pragma once
#include "String.h"
#include "GameObject.h"
#include "Player.h"

class Player;

class Item : public GameObject
{
public:
	Item();
	Item(String name, String desc);
	~Item();

	String GetName() { return m_name; }
	void SetName(String& str) { m_name = str; }

	static bool Compare(Item* p1, Item* p2);

	void Draw() override;
	void DrawDescription() override;

	String GetDescription() { return m_description; }

	virtual void OnPickup(Player* pPlayer) = 0;

protected:
	String m_name;
	String m_description;
};

