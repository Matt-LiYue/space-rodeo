#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include "sr-control.h"
#include "sr-utils.h"



Control::Control(){
  _levelfinished = false;
  _crash=false;
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
  _ship->updateGuideline(_planets, _wormholes, _asteroids);
	_ship->updateAnimation();
	//_ship->getGuideline()->applyEffects(_planets,_wormholes,_asteroids,_cows);
  
  /* map exit */
  if (pos.x < -100 || pos.y < -100 || pos.x > WINDOW_WIDTH+100 || pos.y > WINDOW_HEIGHT+100) { 
    die();
  }
  
  /* GRAVITY --> ORBIT state change (change when ship perpendicular to planet)*/
  if (_ship->getState() == Ship::GRAVITY) {
    assert(_ship->getOrbitPlanet() != NULL);
    sf::Vector2f shipToPlanet = _ship->getOrbitPlanet()->getPosition() - _ship->getPosition();
    if (utils::dot(shipToPlanet, _ship->getSpd()) <= 0) {
      _ship->setState(Ship::ORBIT);
      _setAngularVelocities(_ship->getOrbitPlanet());
			_ship->spdSaved = utils::norm(_ship->getSpd()); // save incoming spd
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
      
      GameSound::collect();
      
    }
  }
  //Ranch
  if (_ship->intersects(_ranch,_ranch->getRadius())) {
    std::cout << "space ranch reached" << std::endl;
    _levelfinished = true;
    GameSound::complete();
    
    
  }
  //Asteroid
  for (int j = 0; j<_asteroids.size();j++){
    Asteroid* asteroid = _asteroids[j];
    if (_ship -> intersects(asteroid)){
      std::cout << "ship hit asteroid\n";
      
      
      GameSound::crash();

      setcrash(true);
      die();
    }
  }
  
  for (int j=0; j < _planets.size(); j++) {
    Planet* planet = _planets[j];
    //Planet

    if (_ship->intersects(planet)) {
      std::cout << "ship hit planet\n";
      
      GameSound::crash();
      
      setcrash(true);
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
    if (pos.x < -200 || pos.x > WINDOW_WIDTH+200 || pos.y < -200 || pos.y>WINDOW_WIDTH+200){
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
		lasso->getAnimation()->advanceFrame();
    lasso->setPosition(lasso->getPosition() + lasso->getSpd() * timeInterval);
    if (lasso->getState() == Lasso::SHOT) {
      sf::Vector2f dest = _ship->getLassoDest();
      float r = lasso->getRadius();

        /* cow intersect */
      for (int j=0; j < _cows.size(); j++) {
        Cow* cow = _cows[j];
        if (lasso->intersects(cow, cow->getRadius())) {
          _removeModel(cow);
          _hud->setcow(_hud->getcow()+1);
          lasso->setState(Lasso::CAUGHT);
          GameSound::collect();
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
    if (event.key.code == sf::Keyboard::Return){//backdoor to finish a level
        _hud->setcow(_hud->getcow()+_cows.size());
        _levelfinished = true;
    }
    if (event.key.code == sf::Keyboard::Space) {
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
					_ship -> resetAccel();
          _ship -> setState(Ship::BURST);
          _hud -> setburst(_hud->getburst()-1);
        }
      }

      
      GameSound::burst();

    }
    else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W){
      _ship->shoot(0);

    }
    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A){
      if (_ship -> getState() == Ship::REST){
        _ship -> updateOrientation(-3); 
      }
      else{
        _ship -> shoot(-1);
      }
    }
    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D){
      if (_ship -> getState() == Ship::REST){
        _ship -> updateOrientation(3);
      }
      else{
        _ship -> shoot(1);
      }
    } 
    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
      _ship->brake(true);  
    }
		else if (event.key.code == sf::Keyboard::LShift) {
			_ship->getGuideline()->showLine = true;
		}
    else if (event.key.code == sf::Keyboard::M){
      GameSound::musicon();
    }
    else if(event.key.code == sf::Keyboard::N){
      GameSound::musicoff();
    }
		
  }
  else if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
      _ship->brake(false);
    }
		else if (event.key.code == sf::Keyboard::LShift) {
			_ship->getGuideline()->showLine = false;
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
	if (utils::dot(sf::Vector2f(1,0), _ship->getSpd()) < 0) theta *= -1;
  _ship->setAngularVelocity(theta);
}

void Control::setHUD(HUD* hud){
  _hud = hud;
}

void Control::die(){
  _hud->setlife(_hud->getlife() - 1);
  if (_hud->getlife() < 0){
    _die = 2;//game over

    GameSound::die();
    
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
bool Control::getcrash(){
  return _crash;
}
void Control::setcrash(bool crash){
  _crash = crash;
}
