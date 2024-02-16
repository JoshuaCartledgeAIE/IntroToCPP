#pragma once
#include "Point2D.h"
#include "GameDefines.h"
#include <vector>

class GameObject;
class Item;
class Player;
class Enemy;

class Room
{
public:
	Room();
	~Room();
	void SetPosition(Point2D position);
	void SetType(int type) { m_type = type; }
	int GetType() { return m_type; }

	void AddGameObject(GameObject* object);
	void RemoveGameObject(GameObject* object);

	void Draw();
	void DrawDescription();
	void LookAt();

	Enemy* GetEnemy();
	Item* GetItem();

	void RandomiseTransitions(Room** map);
	void AddTransition(int t, Room** map, bool addInverse);

	std::vector<int> GetTransitions() { return m_transitions; }

private:

	Point2D m_mapPosition;
	int m_type;

	std::vector<GameObject*> m_objects;
	std::vector<int> m_transitions;
};

