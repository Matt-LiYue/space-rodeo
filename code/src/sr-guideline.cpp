#include "sr-guideline.h"

Guideline::Guideline() {
  /* tweakables */
  _segLength = 5;
  _fullLength = 1000;
  
	
  showLine = true;

	//_gravityAim = false;
	//_curLength = _fullLength;
  //setPrimitiveType(sf::LinesStrip);
  //resize(_segments + 1);
	//_fullLine.setPrimitiveType(sf::Lines);
	//_fullLine.resize(2);
}

void Guideline::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	std::cout << "guideline drawing\n";
	//target.draw(_fullLine, states);
	for (int i=0; i < _vArrays.size(); i++) {
		target.draw(_vArrays[i]);
	}
}


void Guideline::setLine(sf::Vector2f start, sf::Vector2f dir, int startPointNdx, 
                        std::vector<Planet*> planets, std::vector<Wormhole*> wormholes) {
													// startPointNdx should be 0 unless called within this fn
													
													std::cout << "start: " << start.x << "," << start.y << std::endl;
	
	int n = startPointNdx;
  float segments = _fullLength / _segLength;
  if (utils::norm(dir) != 1) dir = dir / utils::norm(dir); // normalize dir
	
	if (n == 0) {
	  _vArrays.clear();
    _linePoints.clear();
	  _linePoints.push_back(start);
	  _linePoints.push_back(start + dir * _fullLength);
	}
	else {
		//return;
	}
	
  for (int i=0; i < wormholes.size(); i++) {
    //if (n > 0) break;
		
		if (wormholes[i]->getOpen() && utils::intersects(_linePoints[n], _linePoints[n+1], *wormholes[i])) {
			/* line will now have two segments due to wormhole, so update representation
			   and call setLine again on the second segment */
			std::cout << "wormhole intersection\n";
	    int destNdx;
	    if (i % 2 == 0) destNdx = i+1;
	    else destNdx = i-1;
			sf::Vector2f firstEnd, secondStart, secondEnd;
		  float d = utils::getLenToIntersect(_linePoints[n], _linePoints[n+1], *wormholes[i]);
			firstEnd = _linePoints[_linePoints.size() - 2] + dir * d;
			secondStart = wormholes[destNdx]->getPosition() + wormholes[destNdx]->getRadius() * dir;
			secondEnd = secondStart + dir * (_fullLength - d);
			_linePoints[_linePoints.size() - 1] = firstEnd;
			_linePoints.push_back(secondStart);
			_linePoints.push_back(secondEnd);
			setLine(start, dir, n + 2, planets, wormholes);
			break;
		}
	}
	std::cout << _linePoints.size() / 2 << " points:\n ";
	for (int i=0; i < _linePoints.size(); i = i+2) {
		_addLinearDotted(_linePoints[i], _linePoints[i+1]);
		std::cout << _linePoints[i].x << "," << _linePoints[i].y << "-->" << 
			_linePoints[i+1].x << "," << _linePoints[i+1].y << std::endl << " ";
	}
	std::cout << std::endl;
}
void Guideline::_addLinearDotted(sf::Vector2f start, sf::Vector2f end) {
	sf::VertexArray var;
	var.setPrimitiveType(sf::Lines);
  var.append(sf::Vertex(start));
	var.append(sf::Vertex(end));
	_vArrays.push_back(var);
}
  /*
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
	*/
	//_fullLine[0] = sf::Vertex(start);
	//_fullLine[1] = sf::Vertex(start + dir * _fullLength);

/*
void Guideline::applyEffects(std::vector<Planet*> planets, std::vector<Wormhole*> wormholes,
		                         std::vector<Asteroid*> asteroids, std::vector<Cow*> cows, int startPointNdx) {
	// always call setLine first
	_curLength = _fullLength;
	_gravityAim = false;
	
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
  
  for (int i=0; i < asteroids.size(); i++) {
		if (utils::intersects(_fullLine[0].position, _fullLine[1].position, *asteroids[i])) {
		  _curLength = utils::getLenToIntersect(_fullLine[0].position, _fullLine[1].position, *asteroids[i]);
		}
	}
  for (int i=0; i < cows.size(); i++) {
	  
	}
*/
