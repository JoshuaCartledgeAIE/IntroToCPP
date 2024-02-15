#pragma once
#include "Point2d.h"
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	~Enemy() {};


	void OnAttacked(int attackPoints);

	void Draw() override;
	void DrawDescription() override;
	void LookAt() override;

};

