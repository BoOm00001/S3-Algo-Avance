#include "stdafx.h"
#include "Dot.h"

Dot::Dot(int x, int y)
{
  this->x = x;
  this->y = y;
}

int Dot::getX() const
{
  return x;
}

int Dot::getY() const
{
  return y;
}

void Dot::setX(int newX)
{
  x = newX;
}

void Dot::setY(int newY)
{
  y = newY;
}

bool Dot::operator==(const Dot& other) const {
 	return this->x == other.x && this->y == other.y;
}
bool Dot::operator!=(const Dot& other) const {
	return !(*this == other); // Reuse your == operator
}



