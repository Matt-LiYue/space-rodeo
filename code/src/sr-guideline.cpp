#include "sr-guideline.h"

Guideline::Guideline() {
  /* tweakables */
  _segments = 100;
  _length = 1000;
  
  draw = true;
  setPrimitiveType(sf::LinesStrip);
  resize(_segments + 1);
}

void Guideline::setLine(sf::Vector2f start, sf::Vector2f dir) {
  float segLength = _length / _segments;
  if (utils::norm(dir) != 1) dir = dir / utils::norm(dir);
  
  this->operator[](0) = sf::Vertex(start);
  for (int i=0; i < _segments; i++) {
    sf::Vertex v(start + (i+1) * segLength * dir);
    if (i % 2 == 0) v.color = sf::Color::Transparent;
    else v.color = sf::Color::White;
    this->operator[](i+1) = v;
  }
}