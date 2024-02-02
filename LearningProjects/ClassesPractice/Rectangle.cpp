#include "Rectangle.h"



void Rectangle::SetHeight(float newHeight)
{
    m_height = newHeight;
}

void Rectangle::SetWidth(float newWidth)
{
    m_width = newWidth;
}

float Rectangle::GetArea()
{
    return m_width * m_height;
}

float Rectangle::GetPerimeter()
{
    return 2*m_width + 2*m_height;
}
