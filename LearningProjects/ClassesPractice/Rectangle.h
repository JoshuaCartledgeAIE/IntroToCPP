#pragma once
class Rectangle
{

	float m_height;
	float m_width;

public:
	void SetHeight(float newHeight);
	void SetWidth(float newWidth);

	float GetArea();
	float GetPerimeter();
};

