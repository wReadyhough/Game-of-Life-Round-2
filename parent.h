#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;
//0/O is Prey 1/X is Predator

const int START_PREDATOR_HEALTH = 7;
const int START_PREY_HEALTH = 1;
const int PREY_REPRODUCTION_THRESHOLD = 2;//10

//Might be easier to make predator & prey classes friend classes.
class Parent{
    int m_health;
    string m_color; //For visualization later, idk if this'll work
    int m_myX;//column
    int m_myY;//row
  public:
    ~Parent();
    int getHealth();
    string getColor();
    void setHealth(int);
    void updateHealth();
    void changeHealth(int);
    void setColor(string);
    void setCoords(int, int);
    int getRow();
    int getCol();
};


class Predator: public Parent{
  
  public:
    Predator(){}
    Predator(int, int);
    bool updateHealth(int);//returns true if now dead.
};

class Prey: public Parent{

  public: 
    Prey(){}
    Prey(int, int);
    bool reproduce();
    void updateHealth(bool);//bool is true if it just reproduced.
};

//class Board: public Predator, public Prey{
class Board: public Parent{
  vector<Prey> m_prey;
  vector<Predator> m_predators;
  vector<vector<int>> m_board; //0:Prey, 1: predator, 2: nothing
  int m_xDim, m_yDim;//columns, rows
  public:
    Board(int, int, int, int);
    void createBoard();
    void addPredPrey(int, int);
    //void sort();// Function to sort Predators and prey but their row, then column. For easier access.
    void printBoard();
    bool eat(int &, int &);
    void update();
    //void preyMove(int*, int*);//
    bool move (int &, int &);
    //int removePrey(int, int);
    int removePrey(int );
    int numPrey();
    int numPredators();
};