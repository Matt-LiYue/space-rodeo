#include <SFML/Graphics.hpp>

namespace utils {

float dot(sf::Vector2f,sf::Vector2f);
float norm_sqrd(sf::Vector2f v);
float norm(sf::Vector2f v);
sf::Vector2f rotate(sf::Vector2f, float);
bool within(float,float,float);
bool withinBox(sf::Vector2f,float,float,float,float);
float linedotdistance( sf::Vector2f, sf::Vector2f, sf::Vector2f);
bool intersects(sf::Vector2f p1, sf::Vector2f p2, sf::CircleShape);
float getLenToIntersect(sf::Vector2f p1, sf::Vector2f p2, sf::CircleShape cs);
float getLenToPerp(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f);
  // length of line from p1 through p2 stopping at point perpendicular to p3

}