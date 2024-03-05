#pragma once
#include "GameDefines.h"
#include <vector>

class GameObject;
class Item;
class Player;
class Enemy;
class Game;

class Room
{
public:
	Room();

	void SetPosition(Point2D position);
	void SetType(int type) { m_type = type; }
	int GetType() { return m_type; }

	void AddGameObject(GameObject* object);
	void RemoveGameObject(GameObject* object);

	void Draw();
	void DrawDescription();

	std::vector<Enemy*> GetEnemies();
	Item* GetItem();

	void RandomiseTransitions(Game* game);
	void ClearTransitions();
	void AddTransition(int t, Game* game, bool addInverse);

	std::vector<int> GetTransitions() { return m_transitions; }

	void SetVisibility(bool vis) { m_isRevealed = vis; }

private:

	Point2D m_mapPosition;
	int m_type;

	std::vector<GameObject*> m_objects;
	std::vector<int> m_transitions;

	bool m_isRevealed;
};

