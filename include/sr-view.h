#ifndef SR_VIEW_H
#define SR_VIEW_H

#include <SFML/Graphics.hpp>
#include "sr-logic.h"



class View {
  public:
		// constructor
	  View(int height, int width, Logic& logic, sf::RenderWindow& window);
		
		// methods
		void drawPlay();
		
	private:
		int _height;
		int _width;
		Logic* _logic;
		sf::RenderWindow* _window;
};

#endif