#include "GameObject.h"

GameObject::GameObject() : m_mapPosition{ 0, 0 }, m_priority{ PRIORITY_DEFAULT }
{
}

GameObject::GameObject(Point2D pos) : m_mapPosition{ pos }, m_priority{ PRIORITY_DEFAULT }
{
}

GameObject::~GameObject()
{
}
