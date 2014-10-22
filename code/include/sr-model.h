#include <SFML/Graphics.hpp>

class CircleModel: public sf::CircleShape{
  public:
    bool _movable;
    bool intersects(sf::CircleShape *other);
    sf::Vector2f getSpd();
    void setSpd(sf::Vector2f);
  protected:
    sf::Vector2f _spd;
};

class Planet: public CircleModel{
  public:
    Planet(sf::Vector2f,int,int,int);
    int getCowno();
    sf::CircleShape getGravityCircle();
  private:
    int _gravitybound;
    int _cow;
};

class Ship : public CircleModel{
  public:
    typedef enum{
      REST,
      FLY,
      BURST,
      ORBIT,
      CRASH,
      FINISH
    }ShipState;
		
    Ship(sf::Vector2f, int, int);
    int getburst();
    ShipState getState();
    void setState(ShipState);
<<<<<<< HEAD
=======
    void adjustSpd(int);
    void setOrbit(Planet*);
    sf::Vector2f getGravityPull();
		
>>>>>>> e1a48c81df092526405118764ff7c84053601cb3
  private:
    ShipState _shipState;
    int _burst;
    Planet* _orbiting;
    sf::Texture _texture;
    sf::Texture* _textpointer;
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
};


class SpaceRanch : public CircleModel{
  public:
   SpaceRanch(sf::Vector2f, int);
};

class Models{
  public:
    Models();
    std::vector<CircleModel*> getcirmodels();
  private:
    std::vector<CircleModel*> _circlemodels;
};
