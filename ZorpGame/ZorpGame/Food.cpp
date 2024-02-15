#include "Food.h"
#include "GameDefines.h"
#include <iostream>

Food::Food() : m_healthPoints{10}
{
	m_priority = PRIORITY_FOOD;
}

Food::Food(Point2D position) : GameObject{ position }, m_healthPoints{ 10 }
{
	m_priority = PRIORITY_FOOD;
}

void Food::Draw()
{
	std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
}

void Food::DrawDescription()
{
	std::cout << INDENT << "You smell a recently extinguished campfire, perhaps left by a previous traveller." << std::endl;
}

void Food::LookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some food here. It should be edible." << std::endl;
}
