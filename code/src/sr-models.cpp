#include "sr-Models.h"


//This Models will be in charge of storing all the elements in a map, and providing proper APIs for the VIEW Class to draw the elements.
Models::Models(int level){//TODO: Read from a txt file to place the elements in map
  if (level == 0){
    _circlemodels.push_back(new Ship(sf::Vector2f(50,300), 20, 5));
		_circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
    _circlemodels.push_back(new Cow(sf::Vector2f(400,300),40));
    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,300),70));
  }
  if (level == 1){
    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
		_circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
    _circlemodels.push_back(new Planet(sf::Vector2f(300,200),70,30));
    _circlemodels.push_back(new Cow(sf::Vector2f(600,400),40));
		_circlemodels.push_back(new Cow(sf::Vector2f(500,200),40));
    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
    _circlemodels.push_back(new Wormhole(sf::Vector2f(600,80),50));
    _circlemodels.push_back(new Wormhole(sf::Vector2f(100,500),50));
    _circlemodels.push_back(new Asteroid(sf::Vector2f(850,-50),30,sf::Vector2f(-80,80)));
  }
	else if (level == 2) {
    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
		//_circlemodels.push_back(new OrbitPlanet(sf::Vector2f(300,200), 40, 30)));
	}
	
	std::cout << "Original models: " << _circlemodels.size() << std::endl;
  for (int i=0; i<_circlemodels.size(); i++) {
    float r = _circlemodels[i]->getRadius();
    sf::Vector2f center = _circlemodels[i]->getPosition();
    _circlemodels[i]->setOrigin(sf::Vector2f(r,r));
    _circlemodels[i]->setPosition(center);
  }
}

std::vector<CircleModel*> Models::getcirmodels(){
  return _circlemodels;
}

std::vector<Animation*> Models::getAnimations() {
	std::vector<Animation*> v;
	for(int i=0; i < _circlemodels.size(); i++) {
		CircleModel* c = _circlemodels[i];
		if (c->hasAnimation) {
			v.push_back(c->getAnimation());
		}
	}
	return v;
}