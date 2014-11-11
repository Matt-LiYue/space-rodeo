#include <SFML/Graphics.hpp>
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
	1 - not in a gravity field: state = FLY, _orbiting = 0
	2 - in a gravity field, not yet orbiting: state = GRAVITY, _orbiting = planet*
	3 - in orbit: state = ORBIT, _orbiting = planet*
	4 - has burst out of orbit, still in gravity field: state = BURST, _orbiting = planet*
	5 - not in a gravity field: state = FLY, _orbiting = 0
	
	State Transitions:
	2 --> 3: at point when ship orientation and line to planet are perpendicular.
	*/
	
  _ship->decelerate();

	
	
	/* map exit */
	sf::Vector2f pos = _ship->getPosition();
  if (pos.x < 0 || pos.y < 0 || pos.x > 800 || pos.y > 600) {std::cout << "screen exit\n"; die();}
	
	/* movement */
	Planet* planet = _ship->getOrbitPlanet();
	if (_ship->getState() == Ship::GRAVITY && 
	  linedotdistance(_ship->getPosition(), _ship->getPosition()+_ship->getSpd(), _ship->getOrbitPlanet()->getPosition()) > _ship->getRadius()+planet->getRadius()) {
			_setAngularVelocities(planet);
	}

	if (_ship->getState() == Ship::ORBIT) {
	  /*_ship->setSpd((planet->getPosition() - _ship->getPosition() + rotate(_ship->getPosition() 
			- planet->getPosition(), timeInterval * _ship->getAngularVelocity())) / timeInterval);
		_ship->setSpd(_ship->getSpd() + planet->getVelocity());
		_ship->setPosition(_ship->getPosition() + _ship->getSpd() * timeInterval);
		*/
		sf::Vector2f planetToShip = _ship->getPosition() - planet->getPosition();
		planetToShip = planetToShip / norm(planetToShip) * planet->getGravityCircle().getRadius();
		float dTheta = 2 * M_PI * timeInterval / _ship->_period;
		sf::Vector2f newPos = planet->getPosition() + rotate(planetToShip, dTheta);
		_ship->setSpd((newPos - _ship->getPosition()) / timeInterval);
		_ship->setPosition(planet->getPosition() + rotate(planetToShip, dTheta));
		
	}
  else { // normal movement
    _ship->setPosition(_ship->getPosition() + _ship->getSpd() * timeInterval);
	}
		
	/* collisions */
	for (int j=0; j < _cows.size(); j++) {
	  Cow* cow = _cows[j];
		if (_ship->intersects(cow)) {
			_removeModel(cow);
			_hud->setcow(_hud->getcow()+1);
			//cow->draw = false; //TODO: better hit cow status
      _gsound.collect();
		}
	}
  
  
	
	if (_ship->intersects(_ranch)) {
    _gsound.complete();
    std::cout << "space ranch reached" << std::endl;
    _levelfinished = true;
  }
		
	//Asteroid
	for (int j = 0; j<_asteroids.size();j++){
    Asteroid* asteroid = _asteroids[j];
    if (_ship -> intersects(asteroid)){
      std::cout << "ship hit asteroid\n";
      die();
    }
  }
	// planet, gravity intersections
	for (int j=0; j < _planets.size(); j++) {
		Planet* planet = _planets[j];
		
		// planet
		if (_ship->intersects(planet)) {
      _gsound.crash();
			std::cout << "ship hit planet\n";
			die();
		}
		
		// gravity field
    sf::CircleShape gravity = planet->getGravityCircle();
    if (_ship->getState() == Ship::FLY && _ship->intersects(&gravity)) {
			std::cout << "entering gravity field with radius " << gravity.getRadius() << std::endl;
			_ship->setOrbit(planet);
			/*if (dynamic_cast<OrbitPlanet*>(planet) != 0) 
				_ship->setState(Ship::ORBIT_GRAVITY);
			else*/
		    _ship->setState(Ship::GRAVITY);
    }
		else if (_ship->getState() == Ship::BURST) {
			if (!_ship->intersects(&gravity)) {
				_ship->setState(Ship::FLY);
				_ship->setOrbit(0);
			}
		}
		else if (_ship->getState() == Ship::GRAVITY && !_ship->intersects(&gravity)) {
			std::cout << "exiting gravity field\n";
			//_setAngularVelocities(planet);
		}
	_ship->updateOrientation();
	}
	/* end ship movement */
		
  //Wormhole
  for (int j=0; j < _wormholes.size();j++){ //Wormhole implementation
    if (_ship->intersects(_wormholes[j])){ //Run into Wormhole
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
				if (lasso->intersects(cow)) {
					//cow->draw = false; //TODO: better hit cow status
					_removeModel(cow);
					_hud->setcow(_hud->getcow()+1);
					lasso->setState(Lasso::CAUGHT);
				}
			}
			
			/* destination intersect (point-circle)*/
			if (lasso->getState() != Lasso::CAUGHT &&
				withinBox(lasso->getPosition(), dest.x - r, dest.x + r, dest.y - r, dest.y + r)) {
				if (norm_sqrd(lasso->getPosition() - dest) < r*r) {
					lasso->setState(Lasso::MISSED);
				}
			}
		}
		else if (lasso->getState() == Lasso::CAUGHT || lasso->getState() == Lasso::MISSED) {			
			sf::Vector2f dir = _ship->getPosition() - lasso->getPosition(); // not normalized
			float d_sqrd = norm_sqrd(dir);
			if (d_sqrd < _ship->getRadius() * _ship->getRadius()) {
				lasso->setState(Lasso::HELD);
				lasso->draw = false;
			}
			lasso->setSpd(dir / norm(dir) * lasso->getLassoSpd());
		}
  }
}
	
void Control::handleEvent(sf::Event event){
  if (event.key.code == sf::Keyboard::Space) {
  	_ship->shoot();
  }

  if (event.key.code == sf::Keyboard::Up){ // Fire the rocket
      if (_ship -> getState() == Ship::REST){
        _ship -> adjustSpd(100);
        _ship -> setState(Ship::FLY);
      }
      else if (_ship -> getState() == Ship::FLY){// TODO: Need a counter
        if (_hud -> getburst() > 0){
          _ship -> adjustSpd(300);
          _hud -> setburst(_hud->getburst()-1);
      }
      }
      else if (_ship -> getState() == Ship::ORBIT) {
      	if (_hud -> getburst() > 0){
        	_ship -> adjustSpd(300);
	      	_ship -> setState(Ship::BURST);
	      	_hud -> setburst(_hud->getburst()-1);
	      }
      }
    _gsound.burst();
  }
  if (event.key.code == sf::Keyboard::Left){
    if (_ship -> getState() == Ship::REST){
      _ship -> rotate(-3); 
    }
  }
  if (event.key.code == sf::Keyboard::Right){
    if (_ship -> getState() == Ship::REST){
      _ship -> rotate(3);
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
	_ship->setState(Ship::ORBIT);
	float theta = sqrt(norm_sqrd(_ship->getSpd()) / norm_sqrd(planet->getPosition() - _ship->getPosition()));
	if (dot(planet->getPosition() - _ship->getPosition(), sf::Vector2f(0,1)) < 1) theta *= -1;
	std::cout << "angular velocity set to " << theta << std::endl;
	_ship->setAngularVelocity(theta);
	
	// base Angular Velocity
	theta = 100 / norm(planet->getPosition() - _ship->getPosition());
	if (dot(planet->getPosition() - _ship->getPosition(), sf::Vector2f(0,1)) < 1) theta *= -1;
	_ship->setBaseAngVelocity(theta);
}

void Control::setHUD(HUD* hud){
	_hud = hud;
}

void Control::die(){
	_hud->setlife(_hud->getlife() - 1);
	std::cout << _hud->getlife();
	if (_hud->getlife() < 0){
		_die = 2;
	}
	else{
		_die = 1;
	}
}
int Control::getdie(){
	return _die;
}
void Control::setdie(int die){
	_die = die;
}