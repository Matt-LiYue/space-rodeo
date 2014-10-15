#include <SFML/Graphics.hpp>
#include <iostream> // dbg
#include "sr-logic.h"
#include "sr-view.h"

/*
Design Overview:
space-rodeo.cpp: contains main game loop with timer. Has logic and view objects.
             Gives the logic object to the view. Processes input and gives it to logic.

sr-logic.h:  Controls all the variables of the game. Note positions are in [0,1] x [0,1].
             Game objects are called sr-models, and the logic has these.

sr-view.h:   Responsible for drawing shapes. Has a pointer to logic so that it can get
             the sr-models to draw

sr-model.h:  A model is a superclass which represents objects such as ship, planet, cow.
             Contains an sf::Shape and a position

sr-ship.h:   Extends the model superclass with more vars like rocket fuel, direction,etc.

*/




int main(int argc, char** argv) {
	const int HEIGHT = 600;
	const int WIDTH = 800;
	
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "Space Rodeo");
  sf::Event event;
	Logic logic;
	View view(HEIGHT, WIDTH, logic, window);
	
  while (window.isOpen()) {
		window.clear(sf::Color::Black);	
		
    while (window.pollEvent(event)) {
			switch (event.type) {
				
        // window closed
        case sf::Event::Closed:
          window.close();
			    break;
					
				default:
					break;
			} // end switch
		} // end event poll
	  window.display();
	}
	
	return 0;
}