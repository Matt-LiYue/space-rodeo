#include "sr-ship.h"

//Ship class
Ship::Ship(sf::Vector2f pos, int radius, int burst){
  // tweakable params
  _lasso = new Lasso(20,100);
	_guideline = new Guideline();
  _lowSpd = 10;
  _baseSpd = 100;
  _boostSpd = 300;
  _brakeMagnitude = 300;
  
  // private vars
  hasAnimation = false;
  _movable = true;
  _orbiting = 0;
  _burst = burst;
  _shipState = Ship::REST;
  _texture.loadFromFile("rock.png");
  _textpointer = &_texture;
  _accel = sf::Vector2f(0,0);
  
  draw = true;
  setTexture(_textpointer);
  setPosition(pos);
  setRadius(radius);
  setOrigin(radius,radius);
  rotate(90);  
}

sf::Vector2f Ship::updatePosition(float deltaTime) {
  sf::Vector2f planPos;
  
  // update velocity
  sf::Vector2f newVelocity = _spd + _accel * deltaTime;
  if (utils::norm(newVelocity) > _baseSpd && utils::norm(_spd) <= _baseSpd) { // don't accel past base spd
    _spd = _baseSpd * _spd / utils::norm(_spd);
    _accel *= 0.f;
  }
  else {
    sf::Vector2f lowVelocity = _lowSpd * _spd / utils::norm(_spd);
    if (utils::dot(lowVelocity, newVelocity) < _lowSpd * _lowSpd)
      _spd = lowVelocity;
    else
      _spd = newVelocity;
  }
  
  if (_shipState == ORBIT) {
    int sign = 1;
    if (_angularVelocity < 0) sign = -1;
    float orbitRadius = utils::norm(getPosition() - _orbiting->getPosition());
    _angularVelocity = sign * utils::norm(_spd) / orbitRadius;
  }

  // update position
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

float Ship::getBaseSpd() {
  return _baseSpd;
}

float Ship::getLowSpd() {
  return _lowSpd;
}

float Ship::getBoostSpd() {
  return _boostSpd;
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

void Ship::brake(bool on) {
  if (utils::norm(_spd) == 0) return; // avoid divide by 0
  if (on) {
    _accel = -1.0f * _spd * _brakeMagnitude / utils::norm(_spd);
    std::cout << "braking, accel set to " << utils::norm(_accel) << std::endl;
  }
  else {
    _accel = _spd * _brakeMagnitude / utils::norm(_spd);
    std::cout << "brake off, accel set to " << utils::norm(_accel) << std::endl;
  }
}

/* deprecated
void Ship::setBaseAngVelocity(float theta) {
  _baseAngVelocity = theta;
}
*/

Lasso* Ship::getLasso() { return _lasso; }

Guideline* Ship::getGuideLine() { return _guideline; }

sf::Vector2f Ship::getLassoDest() {return _lassoDest; }

void Ship::shoot() {
  float offset = getRadius()+_lasso->getRadius();
  sf::Vector2f dir = sf::Vector2f(cos(getDir()* M_PI/180),sin(getDir()* M_PI / 180)) ;
  _lasso->setSpd(dir * _lasso->getLassoSpd());
  _lasso->setPosition(getPosition() + dir * offset);
  _lassoDest = sf::Vector2f(_lasso->getPosition() + dir * _lasso->getLength());
  _lasso->setState(Lasso::SHOT);
  _lasso->draw = true;
}

void Ship::updateGuideline(bool on) {
	draw = on;
	float theta = getDir() * M_PI / 180;
	_guideline->setLine(getPosition(), sf::Vector2f(cos(theta),sin(theta)));
}

/* deprecated
void Ship::decelerate(){
  if (_shipState == FLY && utils::norm_sqrd(getSpd()) > _baseSpd*_baseSpd){
    setSpd(getSpd()*0.998f);
    if (utils::norm_sqrd(getSpd()) <= _baseSpd*_baseSpd){
      adjustSpd(_baseSpd);
    }
  }
}
*/



