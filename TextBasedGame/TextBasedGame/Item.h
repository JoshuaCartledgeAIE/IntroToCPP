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

	String GetName() { return m_name; }
	void SetName(String& str) { m_name = str; }

	static bool Compare(Item* p1, Item* p2);

	void Draw() override;
	void DrawDescription() override;

	String GetDescription() { return m_description; }

	// OnPickup gives the player the benefit of the item
	virtual void OnPickup(Player* pPlayer) = 0;
	// OnStolen reverses the benefit of the item (when enemy steals it from you)
	virtual void OnStolen(Player* pPlayer) = 0;

protected:
	String m_name;
	String m_description;
};

