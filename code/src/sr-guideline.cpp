#include "sr-guideline.h"

Guideline::Guideline() {
  /* tweakables */
  _segLength = 5;
  _fullLength = 500;
  showLine = false;

}

void Guideline::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (int i=0; i < _vArrays.size(); i++) {
    target.draw(_vArrays[i]);
  }
}


void Guideline::setLine(sf::Vector2f start, sf::Vector2f dir, int startPointNdx, 
                        std::vector<Planet*>& planets, std::vector<Wormhole*>& wormholes) {
                          // startPointNdx should be 0 unless called within this fn
                          
  
  int n = startPointNdx;
  if (n > 20) return;
  
  if (utils::norm(dir) != 1) dir = dir / utils::norm(dir); // normalize dir
  
  if (n == 0) {
    _vArrays.clear();
    _linePoints.clear();
		sf::Vector2f cushion = dir * 20.f;
    _linePoints.push_back(start + cushion );
    _linePoints.push_back(start + dir * _fullLength);
  }
  
  for (int i=0; i < wormholes.size(); i++) {
    
    if (wormholes[i]->getOpen() && utils::intersects(_linePoints[n], _linePoints[n+1], *wormholes[i])) {
      /* line will now have two segments due to wormhole, so update representation
         and call setLine again on the second segment */
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
      return;
    }
  }
  
  sf::CircleShape gravity;
  for (int i=0; i < planets.size(); i++) {
    gravity = planets[i]->getGravityCircle();
    if (utils::intersects(_linePoints[n], _linePoints[n+1], *planets[i])) {
      float d = utils::getLenToIntersect(_linePoints[n], _linePoints[n+1], *planets[i]);
      _linePoints[n+1] = _linePoints[n] + dir * d;
    }
    else if (utils::intersects(_linePoints[n], _linePoints[n+1], gravity)) {
      float d = utils::getLenToPerp(_linePoints[n], _linePoints[n+1], gravity.getPosition());
      _linePoints[n+1] = _linePoints[n] + dir * d;
      _addCircleDotted(gravity.getPosition(), utils::norm(_linePoints[n+1] - gravity.getPosition()));
      
    }
  }
  
  for (int i=0; i < _linePoints.size(); i = i+2) {
    _addLinearDotted(_linePoints[i], _linePoints[i+1], dir);
  }
}

void Guideline::_addCircleDotted(sf::Vector2f center, float r) {
  sf::VertexArray var;
  var.setPrimitiveType(sf::Lines);
  float circum = r * M_PI * 2;
  float segs = circum / _segLength;
  for (int i=0; i < segs; i++) {
    float theta = 2 * M_PI * i / segs;
    var.append(sf::Vertex(center + sf::Vector2f(r * cos(theta), r * sin(theta))));
  }
  _vArrays.push_back(var);
}

void Guideline::_addLinearDotted(sf::Vector2f start, sf::Vector2f end, sf::Vector2f dir) {
  sf::VertexArray var;
  var.setPrimitiveType(sf::Lines);
  float length = utils::norm(end - start);
  float segs = length / _segLength;
  for (int i=0; i < segs; i++) {
    var.append(sf::Vertex(start + dir * (float) i / segs * length));
  }
  _vArrays.push_back(var);
}
