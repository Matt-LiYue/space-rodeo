#ifndef _H_SR_GUIDELINE_
#define _H_SR_GUIDELINE_

#include "SFML/Graphics.hpp"
#include "sr-utils.h"
#include "sr-planet.h"
#include "sr-wormhole.h"
#include "sr-cow.h"
#include "sr-asteroid.h"
#include <iostream>

class Guideline : public sf::Drawable {
  public:
    Guideline();
    bool showLine;
    //float length;
    void setLine(sf::Vector2f start, sf::Vector2f dir, int startPointNdx,
		             std::vector<Planet*>&, std::vector<Wormhole*>&,
								 std::vector<Asteroid*>&);
								 // use 0 for startPointNdx
  private:
		float _segLength;
		float _fullLength;
		std::vector<sf::VertexArray> _vArrays;
		std::vector<sf::Vector2f> _linePoints;
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		void _addLinearDotted(sf::Vector2f start, sf::Vector2f end, sf::Vector2f  dir);
    void _addCircleDotted(sf::Vector2f center, float radius);
};




#endif