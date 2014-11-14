#include "sr-models.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


//This Models will be in charge of storing all the elements in a map, and providing proper APIs for the VIEW Class to draw the elements.
Models::Models(int level){//TODO: Read from a txt file to place the elements in map
  _currentlevel = level;
  _hud.initialize(30, sf::Vector2f(650,50),3,3,0);
  parse();
  
 //if (level == 0){
 //   parse();
 //    _circlemodels.push_back(new Ship(sf::Vector2f(50,300), 20, 5));
//		_circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
//    _circlemodels.push_back(new Cow(sf::Vector2f(400,300),40));
//    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,300),70));
//  }
//  if (level == 1){
//    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
//		_circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
//    _circlemodels.push_back(new Planet(sf::Vector2f(300,200),30,70));
//    _circlemodels.push_back(new Cow(sf::Vector2f(600,400),40));
//		_circlemodels.push_back(new Cow(sf::Vector2f(500,200),40));
//    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
//    _circlemodels.push_back(new Wormhole(sf::Vector2f(600,80),50));
//    _circlemodels.push_back(new Wormhole(sf::Vector2f(100,500),50));
//    _circlemodels.push_back(new Asteroid(sf::Vector2f(850,-50),30,sf::Vector2f(-80,80)));
//  }
//	else if (level == 2) {
//    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 2));
//		//_circlemodels.push_back(new OrbitPlanet( sf::Vector2f(250,150),150,50,100,12,25,50));
//    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
//		_circlemodels.push_back(new OrbitPlanet( sf::Vector2f(200,200),60,60,100,3,20,50));
//    //_circlemodels.push_back(new Planet(sf::Vector2f(300,200),30,70));
//		
//		//_circlemodels.push_back(new Planet(sf::Vector2f(500,200),20,50));
//	}
  std::cout << "Original models: " << _circlemodels.size() << std::endl;
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

void Models::restart(){
  _circlemodels.clear();
  parse();
}

HUD& Models::getHUD(){
  return _hud;
}

int Models::getcowno(){
  return _totalcow;
}

void Models::parse(){
  char c;
  int x = 0;
  int y = 1;
  int width, height;
  _totalcow = 0;
  std::string currentlevel;
  std::stringstream out;
  out << _currentlevel;
  currentlevel = out.str();
  std::string filename = "level" + currentlevel + ".txt";
  std::ifstream input;
  input.open(filename.c_str());
  
  if(input.fail()){
    std::cout << "ERROR: File did not open";
    exit(1);
  }
  
  while (input.good()) {
    c = input.get();
    //std::cout << c;
    
    if (c == '\n'){
      y += 1;
      x = 0;
    }
    else {
      x += 1;
    }
    
    //std::cout << "x,y: " << x << "," << y << "\n";
    switch (c){
      case 'S':
      width = x * 100 - 50;
      height = y * 100;
      _circlemodels.push_back(new Ship(sf::Vector2f(width,height), 20, 5));
      _circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
      break;

      case 'C':
      width = x * 100 - 50;
      height = y * 100;
      _circlemodels.push_back(new Cow(sf::Vector2f(width,height),20));
      _totalcow++;
      break;

      case 'P':
      width = x * 100 - 50;
      height = y * 100;
      _circlemodels.push_back(new Planet(sf::Vector2f(width,height),30,50));
      break;

      case 'R':
      width = x * 100 - 50;
      height = y * 100;
      _circlemodels.push_back(new SpaceRanch(sf::Vector2f(width,height),70));
      break;
      
      case 'W':
      width = x * 100 - 50;
      height = y * 100;
      _circlemodels.push_back(new Wormhole(sf::Vector2f(width,height),50));
      break;
      
      case 'A':
      width = x * 100 + 100;
      height = y * 100 + 100;
      _circlemodels.push_back(new Asteroid(sf::Vector2f(width,height),30,sf::Vector2f(-80,80)));
      break;

      case 'O':
      width = x * 100 - 50;
      height = y * 100;
      _circlemodels.push_back(new OrbitPlanet( sf::Vector2f(width,height),60,60,100,3,20,50));

      default:
      break;
    }
    

    
  }	

  for (int i=0; i<_circlemodels.size(); i++) {
    float r = _circlemodels[i]->getRadius();
    sf::Vector2f center = _circlemodels[i]->getPosition();
    _circlemodels[i]->setOrigin(sf::Vector2f(r,r));
    _circlemodels[i]->setPosition(center);
  }
}
