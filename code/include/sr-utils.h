#include <SFML/Graphics.hpp>

namespace utils {
	
float dot(sf::Vector2f,sf::Vector2f);
float norm_sqrd(sf::Vector2f v);
float norm(sf::Vector2f v);
sf::Vector2f rotate(sf::Vector2f, float);
bool within(float,float,float);
bool withinBox(sf::Vector2f,float,float,float,float);
float linedotdistance( sf::Vector2f, sf::Vector2f, sf::Vector2f);
}