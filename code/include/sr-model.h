#include <SFML/Graphics.hpp>

class CircleModel: public sf::CircleShape{
  public:
    bool _movable;
    sf::Vector2f getSpd();
    void setSpd(sf::Vector2f);
  protected:
    sf::Vector2f _spd;
};

class Ship : public CircleModel{
  public:
    Ship(sf::Vector2f, int, int);
  private:
    int _burst;
};

class Planet: public CircleModel{
  public:
    Planet(sf::Vector2f,int,int,int);
    int getCowno();
  private:
    int _gravitybound;
    int _cow;
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

class Models{
  public:
    Models();
    std::vector<CircleModel*> getcirmodels();
  private:
    std::vector<CircleModel*> _circlemodels;
};
