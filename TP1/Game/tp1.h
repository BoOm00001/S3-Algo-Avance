#pragma once


#include "SquareFinder.h"
#include "FinderType.h"
class TP1
{
public:
	static const unsigned int SCREEN_WIDTH;
	static const unsigned int SCREEN_HEIGHT;
	TP1();
	void run(const std::string& filename);
	void draw(sf::RenderWindow& window)const ;

	
private:
	sf::VertexArray xAxis;
	sf::VertexArray yAxis;
	SquareFinder squareFinder;
	bool isOver;
  FinderType finderType;
	bool init(const std::string& filename);
		
	void handleEvents();
		
	sf::RenderWindow window;
	
	
};

