#pragma once
#include "Dot.h"
#include "Square.h"
#include <string>
#include <iostream>
#include "SquareSide.h"

class SquareFinder
{

public:
	static const unsigned int MAX_SQUARE;
	SquareFinder();
	~SquareFinder();

	const Dot& getDot(unsigned int index) const;
	unsigned int getNbDots() const;
	const Square* getSquares() const;
	unsigned int getNbSquares() const;
	void loadDotsFromMemory(std::stringstream& content);
	void addDot(const Dot& newDot);
	void findSquaresOptimized();
	void findSquaresBruteForce();
	bool isSquareInList(const Square& squareToCheck, Square* squares, int nbSquares) const;

private:
	Dot* dots;
	unsigned int nbDots;


	Square* squares;
	unsigned int nbSquares;

	static bool isLowerThan(const Dot& left, const Dot& right) ;
	int squareDistance(const Dot& p1, const Dot& p2) const;
	bool doesDotExist(const Dot& point) const;
	bool isSquare(const Dot& a, const Dot& b, const Dot& c, const Dot& d) ;
	bool isSideInList(const Side& squareToCheck, Side* sides, int nbSides);
	void bubleSort(int* array, int arraySize);
	bool verifyDistinctDots(const Dot& dot1,const Dot& dot2,const Dot& dot3,const Dot& dot4) const;
	void sortDots(Dot* dots, int nbDotsArray) ;
	Side* findPotentialSquareSides(int& ndOfSideFound);
	Side* addSide(Side* sideArray, int sideArraySize, Side sideToAdd);
	Dot findMatchingDotsForSide(const Side& side) const;



};
