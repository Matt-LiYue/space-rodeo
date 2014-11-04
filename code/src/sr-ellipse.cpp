#include "sr-ellipse.h"
#include "math.h"
#include <iostream>

Ellipse::Ellipse(float xRadius, float yRadius, int numPoints) {
	std::cout << "creating ellipse\n";
	
	_xRad = xRadius;
	_yRad = yRadius;
	setPointCount(numPoints);
	for (int i=0; i < numPoints; i++) {
		float theta = 2 * M_PI * i / numPoints;
		setPoint(0, sf::Vector2f(_xRad * cos(theta), _yRad * sin(theta)));
	}
}

float Ellipse::xRad() { return _xRad; }
float Ellipse::yRad() { return _yRad; }
