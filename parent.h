#include<iostream>

using namespace std;

const int START_PREDATOR_HEALTH = 7;
const int START_PREY_HEALTH = 1;
const int PREY_REPRODUCTION_THRESHOLD = 10;

//Might be easier to make predator & prey classes friend classes.
class Parent{
    int m_health;
    string m_color; //For visualization later, idk if this'll work
  public:
    int getHealth();
    string getColor();
    void setHealth(int);
    void setColor(string);
    /*virtual bool move() = 0;//Returns true if needs to reproduce
    virtual void reproduce() = 0;
    virtual void update() = 0;*/
    
};


class Predator: public Parent{
  public:
    Predator();
    bool move();//Returns true if needs to reproduce
    void reproduce();
    void update();
};

class Prey: public Parent{
  public: 
    Prey();
    bool move();//Returns true if needs to reproduce
    void reproduce();
    void update();
};