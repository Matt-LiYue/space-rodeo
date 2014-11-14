#include <SFML/Graphics.hpp>
#include "sr-view.h"
#include <iostream>

View::View(){
  _bgtexture.loadFromFile("bg.jpg");
  _bgsprite.setTexture(_bgtexture);
  _view.create(sf::VideoMode(800,600,32),"Space Rodeo");
}


void View::setController(Control& controller){
  _controller = &controller;
}

void View::drawHUD(HUD& hud){
  hud.update();
  _view.draw(hud.getcowicon());
  _view.draw(hud.getbursticon());
  _view.draw(hud.getlifeicon());
  _view.draw(hud.gettext());
}
void View::clear(){
  _view.clear(sf::Color::Black);
}
void View::display(){
  _view.display();
}


void View::drawAll(std::vector<CircleModel*>& mycirmodels){
  _view.draw(_bgsprite);
  while (_view.pollEvent(_event)){//TODO: Use Control Class to handle the event
    switch (_event.type){
			
      case sf::Event::Closed:
        _view.close();
        break;
				
      case sf::Event::KeyPressed:
        _controller->handleEvent(_event);
        break;
				
      case sf::Event::KeyReleased:
        _controller->handleEvent(_event);
        break;
				
      default:
        break;
				
    }
  }
  for (int i = 0; i < mycirmodels.size(); i++) {
		if (mycirmodels[i]->draw) {
			if (mycirmodels[i]->hasAnimation) {
				_view.draw(*mycirmodels[i]->getAnimation());
			}
      else {
				_view.draw(*mycirmodels[i]);
			}
		}
	}

}

bool View::isRun(){
  if (_view.isOpen())
    return true;
  else
    return false;
}
