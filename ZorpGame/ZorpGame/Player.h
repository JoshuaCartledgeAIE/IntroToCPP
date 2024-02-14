#pragma once
#include "Point2D.h"
#include "Powerup.h"
#include <vector>

class Room;

class Player {
public:

	Player();
	Player(Point2D position);
	~Player();

	void AddPowerup(Powerup* pUp);

	void SetPosition(Point2D position);
	Point2D GetPosition();

	void Draw();

	bool ExecuteCommand(int command);

private:
	Point2D m_mapPosition;

	std::vector<Powerup*> m_powerups;

	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};

