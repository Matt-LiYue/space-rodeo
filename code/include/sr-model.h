#include <SFML/Graphics.hpp>
#include "sr-animation.h"
class HUD{
  public:
    HUD();
    void initialize(int, sf::Vector2f, int, int, int);
    sf::CircleShape geticon();
    void settext(std::string);
    sf::Text gettext();
  private:
    sf::Font _font;
    sf::CircleShape _icon;
    sf::Text _text;
    sf::Texture _texture;
    sf::Texture* _textpointer;
    int _burst;
    int _cow;
    int _life;
};

class CircleModel: public sf::CircleShape{
  public:
    bool _movable;
		bool draw;
    bool intersects(sf::CircleShape *other);
    sf::Vector2f getSpd();
    void setSpd(sf::Vector2f);
		Animation* getAnimation();
		void setPosition(sf::Vector2f);
		bool hasAnimation;
		
  protected:
    sf::Vector2f _spd;
		Animation _animation;
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


class Asteroid : public CircleModel{
  public:
    Asteroid(sf::Vector2f,int,sf::Vector2f);
    void replay();
    bool getExist();
    void setExist(bool);
  private:
    sf::Vector2f _oripos;
    sf::Texture _texture;
    sf::Texture * _textpointer;
    bool _exist;
};


class Wormhole: public CircleModel{
  public:
    Wormhole(sf::Vector2f,int);
    bool getOpen();
    void setOpen(bool);
  private:
    bool _open;
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
		
	private:
		float _length;
		float _lassoSpd;
    LassoState _lassoState;
    sf::Texture _texture;		
		
};

class Ship : public CircleModel{
	
	/* Constructor and types */
  public:
    typedef enum {
      REST,
      FLY,
			GRAVITY,
      BURST,
      ORBIT } ShipState;
			
    Ship(sf::Vector2f, int, int);
		
		/* accessors */
    int getburst();
    ShipState getState();
    Planet* getOrbitPlanet();
		float getDir();
    float getAngularVelocity();
		Lasso* getLasso();
		sf::Vector2f getLassoDest();
		
		/* mutators */
    void setState(ShipState);
    void setSpd(sf::Vector2f);
    void setOrbit(Planet*);
    void setBaseAngVelocity(float);
		void setAngularVelocity(float);
    void updateOrientation();
    void adjustSpd(int);
		void brake();
    void decelerate();
		void shoot();
		
  private:
    ShipState _shipState;
    int _burst;
    float _angularVelocity;
		float _baseAngVelocity;
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
		std::vector<Animation*> getAnimations();
    HUD getHUD();
  private:
    std::vector<CircleModel*> _circlemodels;
    HUD _hud;
    int totallevel;
    int currentlevel;
};
