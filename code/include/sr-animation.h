#ifndef _SR_ANIMATION_H_
#define _SR_ANIMATION_H_

#include <SFML/Graphics.hpp>

class Animation : public sf::Sprite {
  public:
    Animation();
    void advanceFrame();
		void setFrame(int frame);
    void setSize(float);
    void addFrame(int x1, int y1, int dx, int dy);
    
  private:
    sf::Texture _texture;
    int _curFrame;
    float _size;
    std::vector<int> _frameCoords;
};


#endif // _SR_ANIMATION_H_