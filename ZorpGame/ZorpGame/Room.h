#pragma once
#include "Point2D.h"
#include <vector>

class GameObject;
class Powerup;
class Player;
class Enemy;
class Food;

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
	Powerup* GetPowerup();
	Food* GetFood();

private:
	Point2D m_mapPosition;
	int m_type;

	std::vector<GameObject*> m_objects;
};

