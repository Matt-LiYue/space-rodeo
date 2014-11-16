#include "sr-utils.h"
#include <math.h>
#include <iostream>

namespace utils {
  
float dot(sf::Vector2f a,sf::Vector2f b) {
  return a.x*b.x + a.y*b.y;
}

float linedotdistance( sf::Vector2f a, sf::Vector2f b, sf::Vector2f p)
{
  sf::Vector2f n = b - a;
  sf::Vector2f pa = a - p;
  sf::Vector2f c = n * (dot( pa, n ) / dot( n, n ));
  sf::Vector2f d = pa - c;
  return sqrt( dot( d, d ) );
}

float norm_sqrd(sf::Vector2f v) {
  return v.x * v.x + v.y * v.y;
}

float norm(sf::Vector2f v) {
  return sqrt(norm_sqrd(v));
}

sf::Vector2f rotate(sf::Vector2f v, float angle) {
  return sf::Vector2f(v.x*cos(angle) - v.y*sin(angle), v.x*sin(angle) + v.y*cos(angle));
}

bool within(float val, float x1, float x2) {
  if (x1 <= val and val <= x2) return true;
  else return false;
}

bool withinBox(sf::Vector2f val, float x1, float x2, float y1, float y2) {
  if (within(val.x,x1,x2) && within(val.y,y1,y2)) return true;
  return false;
}

bool intersects(sf::Vector2f p1, sf::Vector2f p2, sf::CircleShape cs) {
	sf::Vector2f c = cs.getPosition();
  if (utils::dot(p2 - p1, c - p1) < 0) return false;
	
	float length = utils::dot(c - p1, p2 - p1) / utils::norm(p2-p1);
	sf::Vector2f scaledLine = p1 + (p2 - p1) / utils::norm(p2-p1) * length;
	sf::Vector2f perp = scaledLine - c;
	if (utils::norm(perp) <= cs.getRadius()) return true;
	else return false;
}

float getLenToIntersect(sf::Vector2f p1, sf::Vector2f p2, sf::CircleShape cs) {
	sf::Vector2f c = cs.getPosition();
	float r = cs.getRadius();
	float length = utils::dot(c - p1, p2 - p1) / utils::norm(p2-p1);
	sf::Vector2f scaledLine = p1 + (p2 - p1) / utils::norm(p2-p1) * length;
	float perpNorm = utils::norm(scaledLine - c);
	float d = length - sqrt(r*r - perpNorm*perpNorm);
	return d;

}

float getLenToPerp(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
	// returns  length of line from p1 through p2 stopping at point perpendicular to p3
	return utils::dot(p3 - p1, p2 - p1) / utils::norm(p2-p1);
}

}