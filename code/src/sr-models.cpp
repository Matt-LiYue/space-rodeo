#include "sr-models.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


//This Models will be in charge of storing all the elements in a map, and providing proper APIs for the VIEW Class to draw the elements.
Models::Models(int level){//TODO: Read from a txt file to place the elements in map
  _currentlevel = level;
  _hud.initialize(30, sf::Vector2f(850,50),3,3,0);
  parse();
  
 //if (level == 0){
 //   parse();
 //    _circlemodels.push_back(new Ship(sf::Vector2f(50,300), 20, 5));
//    _circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
//    _circlemodels.push_back(new Cow(sf::Vector2f(400,300),40));
//    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,300),70));
//  }
//  if (level == 1){
//    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 5));
//    _circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
//    _circlemodels.push_back(new Planet(sf::Vector2f(300,200),30,70));
//    _circlemodels.push_back(new Cow(sf::Vector2f(600,400),40));
//    _circlemodels.push_back(new Cow(sf::Vector2f(500,200),40));
//    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
//    _circlemodels.push_back(new Wormhole(sf::Vector2f(600,80),50));
//    _circlemodels.push_back(new Wormhole(sf::Vector2f(100,500),50));
//    _circlemodels.push_back(new Asteroid(sf::Vector2f(850,-50),30,sf::Vector2f(-80,80)));
//  }
//  else if (level == 2) {
//    _circlemodels.push_back(new Ship(sf::Vector2f(50,80), 20, 2));
//    //_circlemodels.push_back(new OrbitPlanet( sf::Vector2f(250,150),150,50,100,12,25,50));
//    _circlemodels.push_back(new SpaceRanch(sf::Vector2f(700,500),70));
//    _circlemodels.push_back(new OrbitPlanet( sf::Vector2f(200,200),60,60,100,3,20,50));
//    //_circlemodels.push_back(new Planet(sf::Vector2f(300,200),30,70));
//    
//    //_circlemodels.push_back(new Planet(sf::Vector2f(500,200),20,50));
//  }
  std::cout << "Original models: " << _circlemodels.size() << std::endl;
}

std::vector<CircleModel*>* Models::getcirmodels(){
  return &_circlemodels;
}

std::vector<Animation*>* Models::getAnimations() {
  /* IMPORTANT: getAnimations relies on _circleModels being in a good state */
  return &_animations;
}

std::vector<sf::Drawable*>* Models::getDrawables() {
  return &_drawables;
}

void Models::restart(){
  _circlemodels.clear();
  _drawables.clear();
  parse();
}

HUD& Models::getHUD(){
  return _hud;
}

int Models::getcowno(){
  return _totalcow;
}

void Models::parse(){
  std::string line;
  std::string s = " ";
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
  
  while (std::getline(input,line)) {
    std::vector<std::string> tokens;
    tokenizer(line, tokens, s);
    //std::cout << line << "\n";
//    for (int i=0; i<tokens.size(); i++) {
//      std::cout << tokens[i] << "\n";
//    }
//    std::cout << "end";
    
    
   std::string s0 = tokens[0];
    char type[s0.size()];
   std::strcpy(type,s0.c_str());
    
    std::string s1 = tokens[1];
    int width = strToInt(s1);
    
    std::string s2 = tokens[2];
    int height = strToInt(s2);
    
    std::string s3 = tokens[3];
    int radius = strToInt(s3);
    
    std::string s4 = tokens[4];
    int gravity = strToInt(s4);

    std::string s5 = tokens[5];
    int burst = strToInt(s5);

    std::string s6 = tokens[6];
    int x = strToInt(s6);

    std::string s7 = tokens[7];
    int y = strToInt(s7);

    std::string s8 = tokens[8];
    int point = strToInt(s8);
    
    std::string s9 = tokens[9];
    int period = strToInt(s9);

    
    
    switch (*type) {
      case 'S':
        _circlemodels.push_back(new Ship(sf::Vector2f(width,height), radius, burst));
        _circlemodels.push_back(((Ship*) _circlemodels.back())->getLasso());
        _drawables.push_back(((Ship*) _circlemodels[_circlemodels.size() - 2])->getGuideline());
        _drawables.push_back(((Ship*) _circlemodels[_circlemodels.size() - 2])->getRope());
        break;
        
      case 'C':
        _circlemodels.push_back(new Cow(sf::Vector2f(width,height),radius));
         _totalcow++;
        break;
        
      case 'P':
        _circlemodels.push_back(new Planet(sf::Vector2f(width,height),radius,gravity));
        break;
        
      case 'R':
        _circlemodels.push_back(new SpaceRanch(sf::Vector2f(width,height),radius));
        break;
        
      case 'W':
        _circlemodels.push_back(new Wormhole(sf::Vector2f(width,height),radius));
        break;
        
      case 'A':
        _circlemodels.push_back(new Asteroid(sf::Vector2f(width,height),radius,sf::Vector2f(x,y)));
        break;
        
      case 'O':
        _circlemodels.push_back(new OrbitPlanet( sf::Vector2f(width,height),x,y,point,period,radius,gravity));
        
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

  for(int i=0; i < _circlemodels.size(); i++) {
    CircleModel* c = _circlemodels[i];
    if (c->hasAnimation) {
      _animations.push_back(c->getAnimation());
    }
  }
}

void Models::tokenizer(const std::string& str, std::vector<std::string>& tokens, std::string& delimiters){
  
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
  std::string::size_type pos     = str.find_first_of(delimiters, lastPos);
  
  while (std::string::npos != pos || std::string::npos != lastPos){
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    lastPos = str.find_first_not_of(delimiters, pos);
    pos = str.find_first_of(delimiters, lastPos);
  }
  
}

int Models::stringToInt(const std::string& str){
  int result;
  std::istringstream ss(str);
  ss.imbue(std::locale::classic());
  ss >> result;
  // return !ss.fail() && ss.eof();
  return result;
}
