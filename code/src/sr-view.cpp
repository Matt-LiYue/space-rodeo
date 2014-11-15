#include <SFML/Graphics.hpp>#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include "sr-control.h"
#include "sr-utils.h"


Control::Control(){
  _levelfinished = false;
  _die = 0;
}


void Control::setmodels(std::vector<CircleModel*>& myModels){
  _cirmodels = &myModels;
  remakemodels();
}

void Control::remakemodels(){
  _cows.clear();
  _wormholes.clear();
  _asteroids.clear();
  _planets.clear();
  _orbitPlanets.clear();
  
/* Store circle models as their derived classes */
  for (int i = 0; i < (*_cirmodels).size(); i++) {
    if (dynamic_cast<Ship*>((*_cirmodels)[i]) != 0)
      _ship = (Ship*) (*_cirmodels)[i];
    else if (dynamic_cast<SpaceRanch*>((*_cirmodels)[i]) != 0)
      _ranch = (SpaceRanch*) (*_cirmodels)[i];    
    else if (dynamic_cast<Cow*>((*_cirmodels)[i]) != 0)
      _cows.push_back((Cow*) (*_cirmodels)[i]);
    else if (dynamic_cast<Wormhole*>((*_cirmodels)[i]) != 0)
      _wormholes.push_back((Wormhole*) (*_cirmodels)[i]);
    else if (dynamic_cast<Asteroid*>((*_cirmodels)[i]) != 0)
      _asteroids.push_back((Asteroid*) (*_cirmodels)[i]);
    else if (dynamic_cast<Planet*>((*_cirmodels)[i]) != 0) {
      _planets.push_back((Planet*) (*_cirmodels)[i]);
      if (dynamic_cast<OrbitPlanet*>((*_cirmodels)[i]) != 0)
        _orbitPlanets.push_back((OrbitPlanet*) (*_cirmodels)[i]);
    }
  }
}

bool Control::getlevelfinished(){
  return _levelfinished;
}

void Control::update(float timeInterval) {
  remakemodels();
  /* orbit planet */
  for (int i=0; i < _orbitPlanets.size(); i++) {
    _orbitPlanets[i]->updatePosition(timeInterval);
  }
  
  /* begin ship movement */
  
  /* Ship States 
  0 - REST
  1 - not in a gravity field: state = FLY, _orbiting = 0
  2 - in a gravity field, not yet orbiting: state = GRAVITY, _orbiting = planet*
  3 - in orbit: state = ORBIT, _orbiting = planet*
  4 - has burst out of orbit, still in gravity field: state = BURST, _orbiting = planet*
  */
  
  //_ship->decelerate(); disabled for now, replace with brake functionality?
  sf::Vector2f pos = _ship->updatePosition(timeInterval);
  _ship->updateOrientation();
  _ship->updateGuideline(true);
  
  /* map exit */
  if (pos.x < 0 || pos.y < 0 || pos.x > WINDOW_WIDTH || pos.y > WINDOW_HEIGHT) { 
    die();
  }
  
  /* GRAVITY --> ORBIT state change (change when ship perpendicular to planet)*/
  if (_ship->getState() == Ship::GRAVITY) {
    assert(_ship->getOrbitPlanet() != NULL);
    sf::Vector2f shipToPlanet = _ship->getOrbitPlanet()->getPosition() - _ship->getPosition();
    if (utils::dot(shipToPlanet, _ship->getSpd()) <= 0) {
      _ship->setState(Ship::ORBIT);
      _setAngularVelocities(_ship->getOrbitPlanet());
    }
  }
  
  // BURST --> FLY state change
  if (_ship->getState() == Ship::BURST) {
    assert(_ship->getOrbitPlanet() != NULL);
    sf::CircleShape gravity = _ship->getOrbitPlanet()->getGravityCircle();
    if (!_ship->intersects(&gravity)) {
      _ship->setState(Ship::FLY);
      _ship->setOrbit(0);
    }
  }
  
  /* collisions */
  //Cow
  for (int j=0; j < _cows.size(); j++) {
    Cow* cow = _cows[j];
    if (_ship->intersects(cow, cow->getRadius() + _ship->getRadius()*0.25)) {
      _removeModel(cow);
      _hud->setcow(_hud->getcow()+1);
      _gsound.collect();
    }
  }
  //Ranch
  if (_ship->intersects(_ranch,_ranch->getRadius())) {
    _gsound.complete();
    std::cout << "space ranch reached" << std::endl;
    _levelfinished = true;
  }
  //Asteroid
  for (int j = 0; j<_asteroids.size();j++){
    Asteroid* asteroid = _asteroids[j];
    if (_ship -> intersects(asteroid)){
      _gsound.crash();
      std::cout << "ship hit asteroid\n";
      die();
    }
  }
  
  for (int j=0; j < _planets.size(); j++) {
    Planet* planet = _planets[j];
    //Planet
    if (_ship->intersects(planet)) {
      std::cout << "ship hit planet\n";
      _gsound.crash();
      die();
    }
    //Gravity
    sf::CircleShape gravity = planet->getGravityCircle();
    if (_ship->getState() == Ship::FLY && _ship->intersects(&gravity)) {
      _ship->setOrbit(planet);
      _ship->setState(Ship::GRAVITY);
      _ship->setRelPos(_ship->getPosition() - planet->getPosition());
    }
  }
  /* end ship movement */
    
  //Wormhole
  for (int j=0; j < _wormholes.size();j++){ //Wormhole implementation
    if (_ship->intersects(_wormholes[j], _wormholes[j]->getRadius())){ //Run into Wormhole
      if (_wormholes[j]->getOpen() == true){
        _wormholes[j]->setOpen(false);
        int target;
        if (j % 2 == 0)
          target = j+1;
        else
          target = j-1;
        _wormholes[target] -> setOpen(false);
        _ship -> setPosition(_wormholes[target]->getPosition());
      }
    }
    else
      _wormholes[j] -> setOpen(true);
  }
  
  /* Asteroid movement */  
  for (int j = 0; j < _asteroids.size(); j++){
    sf::Vector2f pos = _asteroids[j]->getPosition();
    _asteroids[j]->setPosition(_asteroids[j]->getPosition() + _asteroids[j]->getSpd() * timeInterval);
    if (pos.x < -200 || pos.x > 1000 || pos.y < -200 || pos.y>800){
      _asteroids[j]->setExist(false);
    }
    if (_asteroids[j] -> getExist() == false){
      _asteroids[j] -> replay(); 
    }
    
    /* asteroid collisions */
    for (int k = 0; k < _asteroids.size();k++){ 
      if (k != j && _asteroids[k]->intersects(_asteroids[j])){
        _asteroids[j]->setExist(false);
      }
    }
  }
  
  /* lasso */
  if (_ship->getLasso()->getState() != Lasso::HELD) {
    Lasso* lasso = _ship->getLasso();
    lasso->setPosition(lasso->getPosition() + lasso->getSpd() * timeInterval);
    if (lasso->getState() == Lasso::SHOT) {
      sf::Vector2f dest = _ship->getLassoDest();
      float r = lasso->getRadius();

        /* cow intersect */
      for (int j=0; j < _cows.size(); j++) {
        Cow* cow = _cows[j];
        if (lasso->intersects(cow, cow->getRadius())) {
          _gsound.collect();
          _removeModel(cow);
          _hud->setcow(_hud->getcow()+1);
          lasso->setState(Lasso::CAUGHT);
        }
      }
        /* destination intersect (point-circle)*/
      if (lasso->getState() != Lasso::CAUGHT &&
        utils::withinBox(lasso->getPosition(), dest.x - r, dest.x + r, dest.y - r, dest.y + r)) {
        if (utils::norm_sqrd(lasso->getPosition() - dest) < r*r) {
          lasso->setState(Lasso::MISSED);
        }
      }
    }
    else if (lasso->getState() == Lasso::CAUGHT || lasso->getState() == Lasso::MISSED) {      
      sf::Vector2f dir = _ship->getPosition() - lasso->getPosition(); // not normalized
      float d_sqrd = utils::norm_sqrd(dir);
      if (d_sqrd < _ship->getRadius() * _ship->getRadius()) {
        lasso->setState(Lasso::HELD);
        lasso->draw = false;
      }
      lasso->setSpd(dir / utils::norm(dir) * lasso->getLassoSpd());
    }
  }
}

void Control::handleEvent(sf::Event event){
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Space) {
      _ship->shoot();
    }
    else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W){
      if (_ship -> getState() == Ship::REST){
        _ship -> adjustSpd(_ship->getBaseSpd());
        _ship -> setState(Ship::FLY);
      }
      else if (_ship -> getState() == Ship::FLY){
        if (_hud -> getburst() > 0){
          _ship -> adjustSpd(_ship->getBoostSpd());
          _hud -> setburst(_hud->getburst()-1);
        }
      }
      else if (_ship -> getState() == Ship::ORBIT) {
        if (_hud -> getburst() > 0){
          _ship -> adjustSpd(_ship->getBoostSpd());
          _ship -> setState(Ship::BURST);
          _hud -> setburst(_hud->getburst()-1);
        }
      }
      _gsound.burst();
    }
    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A){
      if (_ship -> getState() == Ship::REST){
        _ship -> rotate(-3); 
      }
    }
    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D){
      if (_ship -> getState() == Ship::REST){
        _ship -> rotate(3);
      }
    } 
    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
      _ship->brake(true);  
    }
  }
  else if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
      _ship->brake(false);
    }
  }
}

void Control::_removeModel(CircleModel* cm) {
  std::vector<CircleModel*>& modelsRef = *_cirmodels;
  CircleModel* tmp = modelsRef[modelsRef.size() - 1];
  
  for (int i = 0; i < modelsRef.size(); i++) {
    if (modelsRef[i] == cm) {
      modelsRef[modelsRef.size() - 1] = cm;
      modelsRef[i] = tmp;
      modelsRef.pop_back();
      break;
    }
  }
}

void Control::_setAngularVelocities(Planet* planet) {
  // initial angular velocity
  float theta = sqrt(utils::norm_sqrd(_ship->getSpd()) / utils::norm_sqrd(planet->getPosition() - _ship->getPosition()));
  if (utils::dot(planet->getPosition() - _ship->getPosition(), sf::Vector2f(0,1)) < 1) theta *= -1;
  _ship->setAngularVelocity(theta);
}

void Control::setHUD(HUD* hud){
  _hud = hud;
}

void Control::die(){
  _hud->setlife(_hud->getlife() - 1);
  if (_hud->getlife() < 0){
    _die = 2;//game over
  }
  else{
    _die = 1;//one life
  }
}
int Control::getdie(){
  return _die;
}
void Control::setdie(int die){
  _die = die;
}

#include "sr-view.h"
#include <iostream>

View::View(){
  _bgtexture.loadFromFile("bg.jpeg");
  _bgsprite.setTexture(_bgtexture);
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  _view.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32),"Space Rodeo", sf::Style::Default, settings);
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


void View::drawAll(std::vector<CircleModel*>& mycirmodels, std::vector<sf::Drawable*>& drawables){
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
  for (int i = 0; i < drawables.size(); i++) {
    sf::Drawable* d = drawables[i];
    if (dynamic_cast<Guideline*>(d) != 0 && ((Guideline*) d)->draw) {
      _view.draw(*d);
    }
  }
  
}

bool View::isRun(){
  if (_view.isOpen())
    return true;
  else
    return false;
}

int View::transitionscreen(int i, int totallevel, bool die, bool insufcow){
  sf::Event event;
  sf::CircleShape icon(30);
  sf::Texture texture;
  sf::Text text;
  sf::Text text2;
  sf::Font font;
  bool select = false;
  font.loadFromFile("arial.ttf");
  text.setFont(font);
  text2.setFont(font);
  texture.loadFromFile("rock.png");
  icon.setTexture(&texture);
  icon.setPosition(300,350);
  text.setPosition(400,350);
  text2.setPosition(350,150);
  text.setCharacterSize(45);
  View::transtate state;
  int result;
    //START SCREEN
  if (die){
    text2.setCharacterSize(50);
    text2.setString("  You die!  \nLevel failed");
    text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
    state = RETRY;
    text.setString("RETRY\n\nEXIT GAME");
  }
  else if (insufcow){
    text2.setCharacterSize(50);
    text2.setString("Capture all cows to finish the level!");
    text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
    state = RETRY;
    text.setString("RETRY\n\nEXIT GAME");
  }
  else{
    if (i == 0){

      text2.setCharacterSize(60);
      text2.setString("SPACE RODEO");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = START;
      text.setString("START GAME\n\nEXIT GAME");
    }
    else if (i == totallevel){
      text2.setCharacterSize(45);
      text2.setString("    Congratulations!\nYou complete this game!");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = RESTART;
      text.setString("MAIN SCEME\n\nEXIT GAME");
    }
    else {
      text2.setCharacterSize(50);
      text2.setString("You finished this level!");
      text2.setPosition(WINDOW_WIDTH/2 - text2.getLocalBounds().width/2, 150);
      state = NEXTLEVEL;
      text.setString("NEXT LEVEL\n\nEXIT GAME");}
    }
    while (_view.isOpen() && !select){
      while (_view.pollEvent(event)){
        switch (event.type){
         case sf::Event::Closed:
         _view.close();
         break;
         case sf::Event::KeyPressed:
         if (event.key.code == sf::Keyboard::Down){
          if (state == START || state == NEXTLEVEL || state == RESTART || state == RETRY){
            state = EXIT;
          }
        }
        if (event.key.code == sf::Keyboard::Up){
          std::cout <<"pressed";
          if (die && state == EXIT){
            state = RETRY;
          }
          if (!die && state == EXIT && i == 0){
            state = START;
          }
          if (!die && state == EXIT && i == totallevel){
            state = RESTART;
          }
          if (!die && state == EXIT && i!=0 && i!=totallevel){
            state = NEXTLEVEL;
          }
        }

        if (event.key.code == sf::Keyboard::Space){
          select = true;
        }
        break;
        default:
        break;
      }
    }
    if (state == EXIT){
      icon.setPosition(300,450);
      result = totallevel;
    }
    else{
      icon.setPosition(300,350);
    }
    if (state == START)
      result = 0;
    if (state == RESTART)
      result = -i;
    if (state == NEXTLEVEL)
      result = 0;
    if (state == RETRY)
      result = -1;

    _view.clear();
    _view.draw(text);
    _view.draw(text2);
    _view.draw(icon);
    _view.display();
  }
  return result;
}
