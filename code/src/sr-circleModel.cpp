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
	if (radiusSum < fabs(diff.x) || radiusSum < fabs(diff.y)) return false;
	if (radiusSum * radiusSum < diff.x*diff.x + diff.y*diff.y) return false;
	return true;
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
