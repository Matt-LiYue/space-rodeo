#ifndef _SR_ANIMATION_H_
#define _SR_ANIMATION_H_

#include <SFML/Graphics.hpp>

class Animation : public sf::Sprite {
  public:
		Animation();
	  void advanceFrame();
		void setSize(float);
		void addFrame(float,float,float,float);
		
  private:
		sf::Texture _texture;
		int _curFrame;
		float _size;
		std::vector<float> _frameCoords;
		void _setFrame(int);
};


#endif // _SR_ANIMATION_H_