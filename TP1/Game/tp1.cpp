#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "tp1.h"
#include "Dot.h"
#include "TPProfLib.h"
const unsigned int TP1::SCREEN_WIDTH = 1024;
const unsigned int TP1::SCREEN_HEIGHT = 1024;

TP1::TP1()
  : isOver(false)
  , xAxis(sf::LinesStrip, 2)
  , yAxis(sf::LinesStrip, 2)
{
}

#pragma region (Code fourni pas � modifier)
void TP1::run(const std::string& filename)
{
  if (!init(filename))
  {
    return;
  }

  while (window.isOpen())
  {
    handleEvents();
    // Si fin de partie atteinte,

    if (isOver)
    {
      // On termine "normalement" l'application
      break;
    }
    else
    {
      window.clear();
      draw(window);
      window.display();
    }

  }
}

void TP1::handleEvents()
{
  sf::Event event;
  //On passe l'�v�nement en r�f�rence et celui-ci est charg� du dernier �v�nement re�u!
  while (window.pollEvent(event))
  {
    //x sur la fen�tre
    if (event.type == sf::Event::Closed)
    {
      window.close();
      isOver = true;
    }
    else if (event.type == sf::Event::KeyPressed)
    {
      if (event.key.code == sf::Keyboard::Num1)
      {
        finderType = FinderType::BRUTE_FORCE;
        squareFinder.findSquaresBruteForce(); 
      }
      else if (event.key.code == sf::Keyboard::Num2)
      {
        finderType = FinderType::OPTIMIZED;
        squareFinder.findSquaresOptimized();
      }
      else if (event.key.code == sf::Keyboard::Escape)
      {
        window.close();
        isOver = true;
      }
    }
  }
}

void TP1::draw(sf::RenderWindow& win)  const
{
  // Dessiner les axes
  win.draw(xAxis);
  win.draw(yAxis);

  // Dessiner les carr�s ici
  const Square* squares = squareFinder.getSquares();
  unsigned int nbSquares = squareFinder.getNbSquares();
  for (unsigned int i = 0; i < nbSquares; i++)
  {
    sf::VertexArray square(sf::LineStrip, 5);
    square[0].position = sf::Vector2f(squares[i].dots[0].getX() + SCREEN_WIDTH * 0.5f, squares[i].dots[0].getY() + SCREEN_HEIGHT * 0.5f);
    square[0].color = sf::Color(255, 255, 255);
    square[1].position = sf::Vector2f(squares[i].dots[1].getX() + SCREEN_WIDTH * 0.5f, squares[i].dots[1].getY() + SCREEN_HEIGHT * 0.5f);
    square[1].color = sf::Color(255, 255, 255);
    square[3].position = sf::Vector2f(squares[i].dots[2].getX() + SCREEN_WIDTH * 0.5f, squares[i].dots[2].getY() + SCREEN_HEIGHT * 0.5f);
    square[3].color = sf::Color(255, 255, 255);
    square[2].position = sf::Vector2f(squares[i].dots[3].getX() + SCREEN_WIDTH * 0.5f, squares[i].dots[3].getY() + SCREEN_HEIGHT * 0.5f);
    square[2].color = sf::Color(255, 255, 255);
    square[4].position = sf::Vector2f(squares[i].dots[0].getX() + SCREEN_WIDTH * 0.5f, squares[i].dots[0].getY() + SCREEN_HEIGHT * 0.5f);
    square[4].color = sf::Color(255, 255, 255);
    win.draw(square);
  }
}

bool TP1::init(const std::string& filename)
{
  window.create(sf::VideoMode(TP1::SCREEN_WIDTH, TP1::SCREEN_HEIGHT, 32), "TP1");
  window.setFramerateLimit(60);

  //Pr�paration des donn�es pour l'affichage des 2 axes
  //Un VertexArray est une collection de points (ici 2 pour le d�but et la fin de l'axe)
  //On stocke le point de d�but et le point de fin de l'axe
  //� l'affichage d'un vertexArray, une droite est trac�e entre les points qu'il contient
  xAxis[0].position = sf::Vector2f((float)0, (float)SCREEN_WIDTH / 2);
  xAxis[1].position = sf::Vector2f((float)SCREEN_WIDTH, (float)SCREEN_WIDTH / 2);
  xAxis[0].color = sf::Color(255, 0, 255);
  xAxis[1].color = sf::Color(255, 0, 255);

  //M�me logique pour l'axe y

  yAxis[0].position = sf::Vector2f((float)SCREEN_WIDTH / 2, 0);
  yAxis[1].position = sf::Vector2f((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT);
  yAxis[0].color = sf::Color(255, 0, 255);
  yAxis[1].color = sf::Color(255, 0, 255);

  std::ifstream file(filename); // Ouvre le fichier en lecture
  if (!file.is_open()) {
    std::cerr << "Impossible d'ouvrir le fichier" << std::endl;
    return 1;
  }

  std::stringstream buffer;
  buffer << file.rdbuf(); // Lit tout le fichier dans le flux buffer

  std::stringstream ss(buffer.str());
  
  squareFinder.loadDotsFromMemory(ss);
  // PROF
  // TODO: Appeler la m�thode findSquaresOptimized() ici une fois que vous l'aurez cod�e
  squareFinder.findSquaresBruteForce();

  return true;
}
#pragma endregion

