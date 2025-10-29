#pragma once
#include <sstream>
class Dot;
struct Square;
class SquareFinder;


// Fonctions de la bibliothèque TPProfLib que les étudiants doivent coder 
bool profIsASquare(const Dot& firstDot, const Dot& secondDot, const Dot& thirdDot, const Dot& fourthDot);
void profReadFileInSquareFinder(std::stringstream& iss, SquareFinder& squareFinder);
void profAddDotToArray(Dot*& dots, unsigned int& nbDots, const Dot& newDot);
void profFindSquaresOptimized(Dot* dots, unsigned int nbDots, Square*& squares, unsigned int& nbSquares);
void profFindSquaresBruteForce(const Dot* dots, unsigned int nbDots, Square*& squares, unsigned int& nbSquares);
