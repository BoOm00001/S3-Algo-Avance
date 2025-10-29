#pragma once
#include "Dot.h"
class Side
{
public:

	static const unsigned int MAX_DOTS ;

	Side(const Dot& dotA, const Dot& dotB);
	Side();
	~Side();
	const double findLength() const;
	const Dot& getPointA() const;
	const Dot& getPointB() const;
	const std::string& getOrientation() const;
	bool operator==(const Side& other) const;

private:
	Dot pointA;
	Dot pointB;
	std::string orientation;  //En fonction de l'orientation du côté je peux determiner l'ordre de recherche du prochain point
	double length;
	void dertermineSideOrientation();

};

