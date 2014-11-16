#include "sr-guideline.h"

Guideline::Guideline() {
  /* tweakables */
  _segments = 100;
  _fullLength = 1000;
  
	
  draw = true;
	_gravityAim = false;
	_curLength = _fullLength;
  setPrimitiveType(sf::LinesStrip);
  resize(_segments + 1);
	_fullLine.resize(2);
}

void Guideline::setLine(sf::Vector2f start, sf::Vector2f dir) {
  float segLength = _curLength / _segments;
  if (utils::norm(dir) != 1) dir = dir / utils::norm(dir);
  
  this->operator[](0) = sf::Vertex(start);
  for (int i=0; i < _segments; i++) {
    sf::Vertex v(start + (i+1) * segLength * dir);
    if (i % 2 == 0) v.color = sf::Color::Transparent;
    else {
			if (_gravityAim) v.color = sf::Color::Green;
			else v.color = sf::Color::White;
		}
    this->operator[](i+1) = v;
  }
	_fullLine[0] = sf::Vertex(start);
	_fullLine[1] = sf::Vertex(start + dir * _fullLength);
}

void Guideline::applyEffects(std::vector<Planet*> planets, std::vector<Wormhole*> wormholes,
		                         std::vector<Asteroid*> asteroids, std::vector<Cow*> cows) {
	// always call setLine first
	_curLength = _fullLength;
	_gravityAim = false;
	
	sf::CircleShape gravity;
  for (int i=0; i < planets.size(); i++) {
	  gravity = planets[i]->getGravityCircle();
		if (utils::intersects(_fullLine[0].position, _fullLine[1].position, *planets[i])) {
		  _curLength = utils::getLenToIntersect(_fullLine[0].position, _fullLine[1].position, *planets[i]);
		}
		if (utils::intersects(_fullLine[0].position, _fullLine[1].position, gravity)) {
		  _gravityAim = true;
		}
	}
  for (int i=0; i < wormholes.size(); i++) {
    int target;
    if (i % 2 == 0)
      target = i+1;
    else
      target = i-1;
		if (utils::intersects(_fullLine[0].position, _fullLine[1].position, *wormholes[i])) {
		  _curLength = utils::getLenToIntersect(_fullLine[0].position, _fullLine[1].position, *wormholes[i]);
		}
	}
  for (int i=0; i < asteroids.size(); i++) {
		if (utils::intersects(_fullLine[0].position, _fullLine[1].position, *asteroids[i])) {
		  _curLength = utils::getLenToIntersect(_fullLine[0].position, _fullLine[1].position, *asteroids[i]);
		}
	}
  for (int i=0; i < cows.size(); i++) {
	  
	}

}