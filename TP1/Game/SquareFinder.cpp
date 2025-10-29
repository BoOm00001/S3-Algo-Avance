#include "stdafx.h"
#include "SquareFinder.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <cmath>  
#include <algorithm>
#include "TPProfLib.h"
#include "SquareSide.h"
#include "Square.h"
const unsigned int SquareFinder::MAX_SQUARE = 20000;

SquareFinder::SquareFinder()
	: nbDots(0)
	, nbSquares(0)
{
	dots = new Dot[nbDots];
	squares = new Square[MAX_SQUARE];
}

SquareFinder::~SquareFinder()
{
	delete[] dots;
	delete[] squares;
}

const Dot& SquareFinder::getDot(unsigned int index) const
{
	if (index < 0 || index >= nbDots)
	{
		throw std::out_of_range("Position invalide");
	}

	return dots[index];
}

unsigned int SquareFinder::getNbDots() const
{
	return nbDots;
}

const Square* SquareFinder::getSquares() const
{
	return squares;
}

unsigned int SquareFinder::getNbSquares() const
{
	return nbSquares;
}

#pragma region "Méthodes à compléter"

void SquareFinder::addDot(const Dot& newDot)
{
	Dot* newArray = new Dot[nbDots + 1];

	for (int i = 0; i < nbDots; ++i)
	{
		newArray[i] = dots[i];
	}

	newArray[nbDots] = newDot;

	delete[] dots;

	dots = newArray;
	nbDots++;

}

Side* SquareFinder::addSide(Side* sideArray, int sideArraySize, Side sideToAdd)
{
	Side* newSideArray = new Side[sideArraySize + 1];

	for (int i = 0; i < sideArraySize; ++i)
	{
		newSideArray[i] = sideArray[i];
	}

	newSideArray[sideArraySize] = sideToAdd;

	delete[] sideArray;

	sideArray = newSideArray;
	return sideArray;
}


void SquareFinder::loadDotsFromMemory(std::stringstream& content)
{
	bool hasValidDot = false;
	std::string element;                           // Je vais être honnêtte,je me suis fait aider par l'IA pour comprendre cette partie.
	while (std::getline(content, element, ';'))   // Prompt Copilot : what does this means std::stringstream& content.
	{                                            // En plus je me suis renseigné sur ce lien: https://stackoverflow.com/questions/20594520/what-exactly-does-stringstream-do
		std::stringstream lineStream(element);
		int x, y;
		char openParen = '(';
		char closeParen = ')';
		char separator = ',';


		if (lineStream >> openParen >> x >> separator >> y >> closeParen)
		{
			addDot(Dot(x, y));
			hasValidDot = true;
		
		}
	}
	if (!hasValidDot)
	{
		throw std::runtime_error("Aucun point valide trouvé dans la chaîne.");  // J'ai décidé d'utiliser runtime error car cet exception se lève l'orsqu'il
	}                                                                           // qu'elque chose d'inatendu s'est passé pendant l'execution du code
}

void SquareFinder::findSquaresBruteForce()
{
	auto startTime = std::chrono::high_resolution_clock::now();
	if (nbDots < 4)
	{
		throw std::runtime_error("Impossible de chercher des carrés : il faut au moins 4 points.");
	}
	bool isDistinctDots = false;
	bool isDistinctSquare = false;

	for (int i = 0; i < nbDots - 3; ++i)  // En décalant les indexes, on évite de vérifier les points différend 
	{
		for (int j = i + 1; j < nbDots - 2; ++j)
		{
			for (int k = j + 1; k < nbDots - 1; ++k)
			{
				for (int l = k + 1; l < nbDots; ++l)
				{

					isDistinctDots = verifyDistinctDots(dots[i], dots[j], dots[k], dots[l]);  // Double verification? Pourquoi pas?

					if (isDistinctDots == true)
					{
						if (isSquare(dots[i], dots[j], dots[k], dots[l])) {  
							Square squareFound;
							squareFound.dots[0] = dots[i];
							squareFound.dots[1] = dots[j];
							squareFound.dots[2] = dots[k];
							squareFound.dots[3] = dots[l];

							isDistinctSquare = isSquareInList(squareFound, squares, getNbSquares());
							if (isDistinctSquare == false)
							{
								squares[nbSquares++] = squareFound;

							}
						}
					}
				}
			}
		}
	}


	auto endTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	std::cout << "findSquaresBruteForce elapsed time = " << elapsedTime * 0.001 << " milliseconds" << std::endl;
	std::cout << "# squares found = " << nbSquares << std::endl;
}

bool SquareFinder::isSquareInList(const Square& squareToCheck, Square* squaresArray, int nbSquares) const // Vérifie dans le tableau de carrés passé  en paramètre squaresArray si le le carré squareToCheck aussi 
{                                                                                                         // passé en paramètre y'est .
	for (int i = 0; i < nbSquares; ++i)
	{
		if (squaresArray[i] == squareToCheck)
			return true;
	}
	return false;
}

bool SquareFinder::isSideInList(const Side& sideToCheck, Side* sides, int nbSides)  //Vérifie si un côté trouvé y est déja dans la liste. Primordial pour eviter les doublons
{
	for (int i = 0; i < nbSides; ++i)
	{
		if (sideToCheck == (sides[i]))
			return true;
	}
	return false;
}


int SquareFinder::squareDistance(const Dot& p1, const Dot& p2) const  // Calcule la distance entre deux points.
{
	int dx = p1.getX() - p2.getX();       // J'utilise une formule trouvée sur Google qui stipule que la distance en deux points dans un plan cartésien
	int dy = p1.getY() - p2.getY();       // peux se calculer avec la formule du carré de la distance euclidienne : (x1​−x2​)2+(y1​−y2​)2
	
	return dx * dx + dy * dy;
}

bool SquareFinder::isSquare(const Dot& a, const Dot& b, const Dot& c, const Dot& d)
{
	// Calcule toutes les distances
	int dists[6];
	dists[0] = squareDistance(a, b);
	dists[1] = squareDistance(a, c);  //Diagonal potentiel
	dists[2] = squareDistance(a, d);
	dists[3] = squareDistance(b, c);
	dists[4] = squareDistance(b, d); // Diagonal potentiel
	dists[5] = squareDistance(c, d);

	bubleSort(dists, 6); // Trie les points pour identifier les côtés et les diagonales qui doivent être normalement les deux dernière données du tableau.

	// Vérifie si les côtés sont égaux aussi que les digonales sont égaux, en plus de vérifier si elles sont plus
	// longues que les côté.
	return dists[0] > 0 && dists[0] == dists[1] && dists[1] == dists[2] && dists[2] == dists[3] && dists[4] == dists[5] && dists[4] > dists[3];
}

bool SquareFinder::isLowerThan(const Dot& left, const Dot& right)
{
	// Filtre les points.

	bool isLowerThan = false;

	if (right.getY() > left.getY())
	{
		isLowerThan = true;
	}
	else if (right.getY() == left.getY())
	{

		if (right.getX() > left.getX())
		{
			isLowerThan = true;
		}
	}
	return isLowerThan;
}



void SquareFinder::sortDots(Dot* dotsArray, int nbDotsArray)
{
	bool hasPermutated = false;
	bool isDotLowerThan = false;
	Dot  temp(0, 0);

	do
	{
		hasPermutated = false;

		for (int i = 0; i < nbDotsArray - 1;++i)
		{
			isDotLowerThan = isLowerThan(dotsArray[i], dotsArray[i + 1]);

			if (isDotLowerThan == true)
			{
				temp = dotsArray[i];
				dotsArray[i] = dotsArray[i + 1];
				dotsArray[i + 1] = temp;
				hasPermutated = true;
			}
		}

	} while (hasPermutated == true);

}

void SquareFinder::bubleSort(int* array, int arraySize)
{
	bool hasPermutated = false;
	int temp = 0;

	do
	{
		hasPermutated = false;

		for (int i = 0; i < arraySize - 1; ++i)
		{
			if (array[i] > array[i + 1])
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				hasPermutated = true;
			}

		}

	} while (hasPermutated);
}

bool SquareFinder::verifyDistinctDots(const Dot& dot1, const Dot& dot2, const Dot& dot3, const Dot& dot4) const
{
	// Vérifie si il n'ya pas le même points plusieurs fois.

	return !(dot1.getX() == dot2.getX() && dot1.getY() == dot2.getY()) && !(dot1.getX() == dot3.getX() && dot1.getY() == dot3.getY()) && !(dot1.getX() == dot4.getX() && dot1.getY() == dot4.getY()) &&
		!(dot2.getX() == dot3.getX() && dot2.getY() == dot3.getY()) && !(dot2.getX() == dot4.getX() && dot2.getY() == dot4.getY()) && !(dot3.getX() == dot4.getX() && dot3.getY() == dot4.getY());
}



Side* SquareFinder::findPotentialSquareSides(int& nbOfPotentialSide)  // Cette fonction vise à trouvé des combinaisons de points qui ont un des deux coordonnée qui correspondent.
{                                                                     // En créant les côté potentiel de carré, je calcule leur distance et j'éviten de rajouter les doublons.
	int sidesArrayLength = 0;
	Side* suqareSidesArray = new Side[sidesArrayLength];

	for (int i = 0; i < nbDots; ++i) {
		for (int j = i + 1; j < nbDots; ++j) {

			if (dots[i].getX() == dots[j].getX() || dots[i].getY() == dots[j].getY()) {

				Side potentialSquareSide = Side(dots[i], dots[j]);
				bool isExistingSide = isSideInList(potentialSquareSide, suqareSidesArray, nbOfPotentialSide);

				if (isExistingSide == false)
				{
					suqareSidesArray = addSide(suqareSidesArray, sidesArrayLength, potentialSquareSide);
					sidesArrayLength++;
					nbOfPotentialSide++;
				}
			}
		}
	}

	return suqareSidesArray;
}


Dot SquareFinder::findMatchingDotsForSide(const Side& side) const                         // Cette fonction à pour but de trouver un points qui a un des même coordonnées qu'un des points du côté potentiel d'un carré.
{                                                                                         // Selon l'orientation du côté, par exemple si le côté est horizontal, alors on cherche un points pour fair un côté vertical 
	// Je me suis peut-être un peu compliqué la vie juste pour chercher un point          // en cherchant un points qui a le même x que un des points du côté potentiel
	double sidelength = side.findLength();
	Dot A = side.getPointA();
	Dot B = side.getPointB();

	for (int i = 0; i < nbDots; ++i)
	{
		Dot dotToTry = dots[i];

		if (!(dotToTry == A || dotToTry == B))
		{
			if (side.getOrientation() == "horizontal") // Si le côté est horizontal alors nous cherchons un point ayant une même coordonné X
			{
				if (dotToTry.getX() == A.getX())
				{
					Side newSquareSide(side.getPointA(), dotToTry);
					if (newSquareSide.findLength() == side.findLength())
					{

						return dotToTry;
					}
				}
				else if (dotToTry.getX() == B.getX())
				{
					Side newSquareSide(side.getPointB(), dotToTry);
					if (newSquareSide.findLength() == side.findLength())
					{
						return dotToTry;
					}
				}
			}
			else if (side.getOrientation() == "vertical")
			{

				if (dotToTry.getY() == A.getY())
				{
					Side newSquareSide(side.getPointA(), dotToTry);
					if (newSquareSide.findLength() == side.findLength())
					{

						return dotToTry;
					}
				}
				else if (dotToTry.getY() == B.getY())
				{

					Side newSquareSide(side.getPointB(), dotToTry);
					if (newSquareSide.findLength() == side.findLength())
					{
						return dotToTry;
					}
				}
			}
		}
	}
	return Dot(-1, -1);
}

bool SquareFinder::doesDotExist(const Dot& point) const
{
	for (int i = 0; i < nbDots; ++i)
	{
		if (dots[i] == point)
			return true;
	}
	return false;
}


void SquareFinder::findSquaresOptimized()
{

	auto startTime = std::chrono::high_resolution_clock::now();

	if (nbDots < 4)
	{
		throw std::runtime_error("Impossible de chercher des carrés : il faut au moins 4 points.");
	}

	int nbOfPotentialSide = 0;
	Dot notMatchingDot(-1, -1);
	bool squareExists = false;

	sortDots(dots, nbDots);
	Side* potentialSquareSidesArray = findPotentialSquareSides(nbOfPotentialSide);

	for (int i = 0; i < nbOfPotentialSide; ++i)
	{
		squareExists = false;
		Side side = potentialSquareSidesArray[i];
		Dot A = side.getPointA();
		Dot B = side.getPointB();

		Dot C = findMatchingDotsForSide(side);
		if (!(C == notMatchingDot))
		{
			Dot D(B.getX() + (C.getX() - A.getX()), B.getY() + (C.getY() - A.getY()));


			if (doesDotExist(D) && isSquare(A, B, C, D))
			{

				Square squareFound;
				squareFound.dots[0] = A;
				squareFound.dots[1] = B;
				squareFound.dots[2] = C;
				squareFound.dots[3] = D;

				for (int i = 0; i < nbSquares; ++i)
				{
					if (squareFound == squares[i])
					{
						squareExists = true;
						break;
					}
				}
				if (!squareExists)
				{
					squares[nbSquares++] = squareFound;

				}
			}
		}

	}
	delete[] potentialSquareSidesArray;

	auto endTime = std::chrono::high_resolution_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
	std::cout << "findSquaresOptimized elapsed time = " << elapsedTime * 0.001 << " milliseconds" << std::endl;
	std::cout << "# squares found = " << nbSquares << std::endl;
}

#pragma endregion