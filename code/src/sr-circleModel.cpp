#include "sr-circleModel.h"

//CircleModel - Base Class of Circle-shaped elements
sf::Vector2f CircleModel::getSpd(){
  return _spd;
}

void CircleModel::setSpd(sf::Vector2f speed){
  _spd = speed;
}

bool CircleModel::intersects(sf::CircleShape *other) {
	sf::Vector2f diff = getPosition() - other->getPosition();
	float radiusSum = getRadius() + other->getRadius();
	if (radiusSum * radiusSum >= diff.x*diff.x + diff.y*diff.y)
		return true;
	else 
		return false;
}

bool CircleModel::intersects(sf::CircleShape *other, float distance) {
	sf::Vector2f diff = getPosition() - other->getPosition();
	if (distance * distance >= diff.x*diff.x + diff.y*diff.y)
		return true;
	else
		return false;
}

void CircleModel::setPosition(sf::Vector2f pos) {
	((sf::CircleShape*) this)->setPosition(pos);
	if (hasAnimation) {
		_animation.setPosition(pos);
	}
}

Animation* CircleModel::getAnimation() {
	return &_animation;
}
