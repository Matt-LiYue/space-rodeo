#ifndef _SR_LASSO_H_
#define _SR_LASSO_H_

#include <SFML/Graphics.hpp>
#include "sr-circleModel.h"


class Lasso : public CircleModel {
  public:
    typedef enum{
      HELD,    // base-state
			SHOT,    // fired
			CAUGHT,  // returning with cow
			MISSED   // returning w/o cow
    } LassoState;
		
	  Lasso(int,float);
		float getLength();
		LassoState getState();
		void setState(LassoState);
		float getLassoSpd();		
		
	private:
		float _length;
		float _lassoSpd;
    LassoState _lassoState;
    sf::Texture _texture;		
		
};

#endif