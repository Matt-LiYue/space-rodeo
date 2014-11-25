#ifndef _SR_UTILS_H_
#define _SR_UTILS_H_
#include <SFML/Graphics.hpp>

class utils {
public:
	static float dot(sf::Vector2f,sf::Vector2f);
	static float norm_sqrd(sf::Vector2f v);
	static float norm(sf::Vector2f v);
	static sf::Vector2f rotate(sf::Vector2f, float radians);
	static bool within(float,float,float);
	static bool withinBox(sf::Vector2f,float,float,float,float);
	static float linedotdistance( sf::Vector2f, sf::Vector2f, sf::Vector2f);
	static bool intersects(sf::Vector2f p1, sf::Vector2f p2, sf::CircleShape);
	static float getLenToIntersect(sf::Vector2f p1, sf::Vector2f p2, sf::CircleShape cs);
	static float getLenToPerp(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f);
  // length of line from p1 through p2 stopping at point perpendicular to p3

};

#endif