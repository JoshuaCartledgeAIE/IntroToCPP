#pragma once
#include "Point2D.h"
class Player {
public:

	Player();
	Player(Point2D position);
	~Player();

	void SetPosition(Point2D position);
	Point2D GetPosition();

	void Draw();

	bool ExecuteCommand(int command);

private:
	Point2D m_mapPosition;
};

