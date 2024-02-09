#pragma once
#include "Point2D.h"

class Room
{
public:
	Room();
	~Room();
	void SetPosition(Point2D position);
	void SetType(int type);
	int GetType();

	void Draw();
	void DrawDescription();
	bool ExecuteCommand(int command);

private:
	Point2D m_mapPosition;
	int m_type;
};

