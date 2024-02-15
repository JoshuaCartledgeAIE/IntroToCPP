#pragma once
#include "GameObject.h"

class Food : public GameObject
{
public:
	Food();
	Food(Point2D position);
	~Food() {}

	int GetHP() { return m_healthPoints; }

	void Draw() override;
	void DrawDescription() override;
	void LookAt() override;

private:
	int m_healthPoints;
};

