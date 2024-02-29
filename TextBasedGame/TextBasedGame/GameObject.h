#pragma once
#include "GameDefines.h"
#include "Point2D.h"

class GameObject
{
public:
	GameObject() ;
	GameObject(Point2D pos);

	Point2D GetPosition() { return m_mapPosition; }
	void SetPosition(Point2D pos) { m_mapPosition = pos; }

	virtual void Draw() = 0;
	virtual void DrawDescription() = 0;

	static bool Compare(const GameObject* p1, const GameObject* p2) { return p1->m_priority < p2->m_priority; }

protected:
	Point2D m_mapPosition;
	int m_priority;

};

