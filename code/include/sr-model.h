#include <SFML/Graphics.hpp>

class CircleModel: public sf::CircleShape{
  public:
    bool _movable;
		bool draw;
    bool intersects(sf::CircleShape *other);
    sf::Vector2f getSpd();
    void setSpd(sf::Vector2f);
		sf::Sprite* getSprite();
		void setPosition(sf::Vector2f);
		bool hasSprite;
		
  protected:
    sf::Vector2f _spd;
		sf::Sprite _sprite;
};

class Planet: public CircleModel{
  public:
    Planet(sf::Vector2f,int,int,int);
    int getCowno();
    sf::CircleShape getGravityCircle();
  private:
    int _gravitybound;
    int _cow;
    sf::Texture _texture;
    sf::Texture* _textpointer;
  
};

class Lasso: public CircleModel {
  public:
    typedef enum{
      HELD,    // base-state
			SHOT,    // fired
			CAUGHT,  // returning with cow
			MISSED   // returning w/o cow
    }LassoState;
		
	  Lasso(int,float);
		float getLength();
		LassoState getState();
		void setState(LassoState);
		float getLassoSpd();
		void advanceFrame();
		
		
	private:
		float _length;
		float _lassoSpd;
    LassoState _lassoState;
    sf::Texture _texture;
		int _curFrame;
		std::vector<float> _frameCoords;
		void _addFrame(float,float,float,float);
		void _setFrame(int);
		
		
};

class Ship : public CircleModel{
  public:
    typedef enum{
      REST,
      FLY,
			GRAVITY,
      BURST,
      ORBIT
    }ShipState;
		
    Ship(sf::Vector2f, int, int);
    int getburst();
    ShipState getState();
    Planet* getOrbitPlanet();
    void setState(ShipState);
    void setSpd(sf::Vector2f);
    void adjustOri(sf::Vector2f);
    void adjustSpd(int);
    void setOrbit(Planet*);
		float getDir();
		void setAngularVelocity(float);
    float getAngularVelocity();
		Lasso* getLasso();
		void shoot();
		sf::Vector2f getLassoDest();
		
  private:
    ShipState _shipState;
    int _burst;
    float _angularVelocity;
    Planet* _orbiting;
    sf::Texture _texture;
    sf::Texture* _textpointer;
		Lasso* _lasso;
		sf::Vector2f _lassoDest;
};

class Cow: public CircleModel{
  public:
    typedef enum{
      FLY,
      WALK
    }CowType;
    Cow(sf::Vector2f,int,Cow::CowType);
  private:
    int _cowValue;
    CowType _cowType;
    CowType getCowType();
    int getCowValue();
    sf::Texture _texture;
    sf::Texture* _textpointer;
};


class SpaceRanch : public CircleModel{
  public:
    SpaceRanch(sf::Vector2f, int);
  private:
    sf::Texture _texture;
    sf::Texture* _textpointer;
};



class Models{
  public:
    Models(int);
    std::vector<CircleModel*> getcirmodels();
		std::vector<sf::Sprite*> getSprites();
  private:
    std::vector<CircleModel*> _circlemodels;
    int totallevel;
    int currentlevel;
};
