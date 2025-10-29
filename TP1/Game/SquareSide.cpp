#include "stdafx.h"
#include "SquareSide.h"
#include <iostream>
#include <string>
#include <sstream>

const unsigned int Side::MAX_DOTS = 2;


Side::Side(const Dot& dotA,const Dot& dotB)
{
	pointA = dotA;
	pointB = dotB;
	length = findLength();
	dertermineSideOrientation();
}
Side::Side()
{

}

Side::~Side()
{
	
}
void Side::dertermineSideOrientation()
{
	bool isHorizontal = false;
	bool isVertical = false;
	if (pointA.getX() == pointB.getX())
	{
		orientation = "vertical";
	}
	else
	{
		orientation = "horizontal";

	}
}
const std::string& Side::getOrientation() const
{
	return orientation;

}

const double Side::findLength() const
{
	double dx = pointA.getX() - pointB.getX();
	double dy = pointA.getY() - pointB.getY();
	return std::sqrt(dx * dx + dy * dy);
}

const Dot& Side::getPointA() const
{
	return pointA;
}
const Dot&  Side::getPointB() const
{
	return pointB;
}

bool Side::operator==(const Side& other) const
{
	return (pointA == other.pointA && pointB == other.pointB) ||
		(pointA == other.pointB && pointB == other.pointA);
}




