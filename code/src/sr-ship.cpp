#include "sr-ship.h"

//Ship class
Ship::Ship(sf::Vector2f pos, int radius, int burst){
  _texture.loadFromFile("rock.png");
	hasAnimation = false;
  _textpointer = &_texture;
  setTexture(_textpointer);
  _burst = burst;
  _lasso = new Lasso(20,100);
  _movable = true;
	draw = true;
  _shipState = Ship::REST;
	_orbiting = 0;
  setPosition(pos);
  setRadius(radius);
  setOrigin(radius,radius);
  rotate(90);	
  _period = 3;
}

sf::Vector2f Ship::updatePosition(float deltaTime) {
	sf::Vector2f planPos;
	switch (_shipState) {
		case REST: break;		
		case FLY:
		  move(deltaTime * _spd);
			break;
		case GRAVITY:
		  planPos = _orbiting->getPosition();
			_relPos += deltaTime * _spd;
		  setPosition(_relPos + planPos);
			break;
		case ORBIT:
  		planPos = _orbiting->getPosition();
		  setSpd((utils::rotate(_relPos, deltaTime * _angularVelocity) - _relPos) / deltaTime);
		  _relPos += deltaTime * _spd;			
			setPosition(_relPos + planPos);
			break;
		case BURST:
		  move(deltaTime * _spd);
			break;	
	}
	return getPosition();
}

void Ship::setRelPos(sf::Vector2f relPos) {
	assert(_orbiting);
	_relPos = relPos;
}

int Ship::getburst(){
  return _burst;
}

Ship::ShipState Ship::getState(){
  return _shipState;
}

void Ship::setState(Ship::ShipState state){
	std::cout << "Ship state " << state << std::endl;
  _shipState = state;
}

void Ship::adjustSpd(int spd){
  setSpd(sf::Vector2f(spd * cos(getDir()*M_PI/180), spd * sin(getDir()*M_PI/180)));
}

void Ship::setOrbit(Planet* planet) {
	_orbiting = planet;
}

float Ship::getDir() { return getRotation() - 90; }

Planet* Ship::getOrbitPlanet() {
  return _orbiting;	
}

void Ship::setAngularVelocity(float av) {
	_angularVelocity = av;
}

float Ship::getAngularVelocity() {
	std::cout << "ship AngularVelocity: " << _angularVelocity << std::endl;
	return _angularVelocity;
}

void Ship::setSpd(sf::Vector2f spd){
  _spd = spd;
}

void Ship::updateOrientation(){
	if (_shipState != REST) {
		float degrees = 180 / M_PI * atan(_spd.y/_spd.x);
		if (fabs(_spd.x) < FLT_EPSILON) degrees = 0;
	  if (_spd.x < 0) degrees += -180;
		setRotation(degrees + 90);
	}
}

void Ship::brake() {

}

void Ship::setBaseAngVelocity(float theta) {
	_baseAngVelocity = theta;
}

Lasso* Ship::getLasso() { return _lasso; }
sf::Vector2f Ship::getLassoDest() {return _lassoDest; }

void Ship::shoot() {
	float offset = getRadius()+_lasso->getRadius();
	sf::Vector2f dir = sf::Vector2f(cos(getDir()* M_PI/180),sin(getDir()* M_PI / 180)) ;
	_lasso->setSpd(dir * _lasso->getLassoSpd());
	_lasso->setPosition(getPosition() + dir * offset);
	_lassoDest = sf::Vector2f(_lasso->getPosition() + dir * _lasso->getLength());
	_lasso->draw = true;
	_lasso->setState(Lasso::SHOT);
}

void Ship::decelerate(){
  if (_shipState == FLY && utils::norm_sqrd(getSpd()) > 100*100){
    setSpd(getSpd()*0.998f);
    if (utils::norm_sqrd(getSpd()) <= 100*100){
      adjustSpd(100);
    }
  }
	/*else if (_shipState == ORBIT && _angularVelocity > _baseAngVelocity) {
		_angularVelocity *= .998f;
	}
	*/
}

/*sf::Vector2f Ship::_getRelPos() {
	assert(_orbiting);
	return getPosition() - _orbiting->getPosition(); // planet --> ship
}
*/

