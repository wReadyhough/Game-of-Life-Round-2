#include "parent.h"
//0/O is Prey 1/X is Predator
//------Parent Stuff------//
Parent::~Parent(){
  m_color = "SHOULD BE DEAD.";
  m_health = -100;
  m_myX = -10;
  m_myY = -10;
}
int Parent::getHealth(){
  return m_health;
}

string Parent::getColor(){
  return m_color;
}

void Parent::setHealth(int health){
  m_health = health;
}

void Parent::setColor(string color){
  m_color = color;
}

void Parent::setCoords(int row, int col){
  m_myX = col;
  m_myY = row;
}

int Parent::getRow(){
  return m_myY;
}

int Parent::getCol(){
  return m_myX;
}


//------Predator Stuff------//
Predator::Predator(int row, int col){
  setColor("Red");
  setHealth(START_PREDATOR_HEALTH);
  setCoords(row, col);
}

//returns true if now dead.
//passed the health of the prey it just ate, 0 for didn't eat, or -1 for error finding prey to remove.
bool Predator::updateHealth(int healthIncrease){
  if(healthIncrease == -1){
    cout<<"Error! Couldn't Find the desired prey to remove!"<<endl;
    throw 20;
  }

  //Didn't eat, decrement health.
  else if(healthIncrease == 0){
    setHealth(getHealth() - 1);
  }
  else{
    setHealth(getHealth() + healthIncrease);
  }

  //Making sure we didn't access a destroyed object's health.
  if(getHealth() < -1){
    cout<<"Error! Accessed destroyed object's health!"<<endl;
    throw 20;
  }

  //Checking for deadness
  if(getHealth() > 0){
    return false;
  }
  return true;
}



//------Prey Stuff------//
Prey::Prey(int row, int col){
  setColor("Green");
  setHealth(START_PREY_HEALTH);
  setCoords(row, col);
}

void Prey::updateHealth(bool reproduced){
  if(reproduced){
    setHealth(START_PREY_HEALTH);
  }
  else{
    setHealth(getHealth() + 1);
  }
}

//Returns true if needs to reproduce
bool Prey::reproduce(){
  return(getHealth() >= PREY_REPRODUCTION_THRESHOLD);
}

//0:Prey, 1: Predator, 2: Nothing
//------Board Stuff------//
Board::Board(int col, int row, int numPredator, int numPrey){
  m_xDim = col;
  m_yDim = row;
  // cout<<"creating board..."<<endl;
  createBoard();
  // cout<<"Adding predators and prey..."<<endl;
  addPredPrey(numPredator, numPrey);
}

void Board::createBoard(){
  vector<int> temp;
  for(int x = 0; x <m_xDim; x++){
    temp.push_back(2);
  }
  for(int y = 0; y < m_yDim; y++){
    m_board.push_back(temp);
  } 
  cout<<"Board created with "<<m_board.size()<<" rows and "<<m_board[0].size()<< " cols"<<endl;

}

void Board::addPredPrey(int numPredator, int numPrey){
  int row, col;
  //Enter predators
  while(numPredator > 0){
    row = rand() % m_yDim;
    col = rand() % m_xDim;
    //Nothing there yet, enter a predator.
    if(m_board[row][col] == 2){
      Predator tempPred(row, col);
      m_predators.push_back(tempPred);
      m_board[row][col] = 1;
      numPredator--;
    }
  }
  while(numPrey > 0){
    row = rand() % m_yDim;
    col = rand() % m_xDim;
    if(m_board[row][col] == 2){
      Prey tempPrey(row, col);
      m_prey.push_back(tempPrey);
      m_board[row][col] = 0;
      numPrey--;
    }
  }
  //cout<<"Board now has "<<m_predators.size()<<" predators and "<<m_prey.size()<<" prey."<<endl;
}

//Predators desiplayed as X, Prey as O, nothing as -
void Board::printBoard(){
  //system("clear");
  cout<<"Prey: O, Predators: X"<<endl;
  for(int y = 0; y < m_yDim; y++){
    for(int x = 0; x < m_xDim; x++){
      switch(m_board[y][x]){
        case 0: //Prey
          cout<<'O';
          break;
        case 1: //Predator
          cout<<'X';
          break;
        case 2: //Nothing
          cout<<'-';
          break;
        default:
          cout<<"Ummmm WHAT???"<<endl;
          break;
      }
    }
    cout<<endl;
  }
}

void Board::update(){
  //News hold where predator/prey will move to. Prevs hold where it was.
  int prevRow = 0, newRow = 0, prevCol = 0,  newCol = 0;
  bool canMove = false, canEat = false, hasDied = false;
  int currPredSize = 0;//Restricts new predators from eating.
  int preyHealth = 0;


  //For now, have newly born prey be initalized wherever. 
  //Later, initialize them where the parent moved from if possible
  cout<<"Moving prey..."<<endl;
  for(int i = 0; i < m_prey.size(); i++){
    
    prevRow = m_prey[i].getRow();
    prevCol = m_prey[i].getCol();
    newRow = prevRow;
    newCol = prevCol;

    canMove = moveOrEat(newRow, newCol,2);

    //Prey Can Move.
    if(canMove == true){
      m_board[prevRow][prevCol] = 2;
      m_board[newRow][newCol] = 0;
      m_prey[i].setCoords(newRow,newCol);
    }
    //Update all prey health
    m_prey[i].updateHealth(false);

  }

  //All prey that can give birth, now do so.
  //Cycle through for the size of the vector.
  //This will make us go through any new borns but, it doesnt matter since they can't give birth yet.
  cout<<"The Baby Boom..."<<endl;
  for(int i = 0; i <m_prey.size(); i++){
    if(m_prey[i].reproduce()){
      m_prey[i].updateHealth(true);
      addPredPrey(0,1);
    }
  }


  cout<<"Moving Predators..."<<endl;
  for(int i = 0; i < m_predators.size(); i++){
    
    prevRow = m_predators[i].getRow();
    prevCol = m_predators[i].getCol();
    newRow = prevRow;
    newCol = prevCol;
    canMove = moveOrEat(newRow, newCol,2);

    //Predator can move
    if(canMove == true){
      m_board[prevRow][prevCol] = 2;
      m_board[newRow][newCol] = 1;
      m_predators[i].setCoords(newRow,newCol);
    }

  }

  cout<<"The Great Massacre..."<<endl;
  currPredSize = m_predators.size();
  for(int i =0; i < currPredSize; i++){

    newRow = m_predators[i].getRow();
    newCol = m_predators[i].getCol();
    //news will hold the location of the prey to be eaten, in the event that true is returned
    canEat = moveOrEat(newRow, newCol,0);

    //Predator has a prey to eat.
    if(canEat == true){
      //Putting a new predator at the prey's location.
      m_board[newRow][newCol] = 1;
      m_predators.push_back(Predator(newRow,newCol));
      preyHealth = removePrey(newRow,newCol);
      hasDied = m_predators[i].updateHealth(preyHealth);
    }
    //Didn't eat, decrease health
    else{
      hasDied = m_predators[i].updateHealth(0);
    }
    //check if dead.
    if(hasDied == true){
      
      m_board[m_predators[i].getRow()][m_predators[i].getCol()] = 2;
      m_predators.erase(m_predators.begin() + i);
      i--;
      currPredSize--;
    }
  }
  //There are no empty spaces on the board at end of this update, randomly clear half the board.
  if((numPredators() + numPrey()) >= (m_yDim * m_xDim)){
    overPopulation(((m_yDim * m_xDim)/2));
  }
  cout<<"Finished updating with "<<m_predators.size()<<" predators and "<<m_prey.size()<<" prey."<<endl;
}

//FOR Move
//If it finds an open space, sets pointers to the coords of that space. 
//If not, pointers should still point to prey's initial spot
//FOR EAT
//If the predator has a prey available for consumption,
//Changes the arguments to the prey's location and returns true
//Otherwise, returns false.
  bool Board::moveOrEat(int &row, int &col, int findMe){
  int r = row;
  int c = col;
  for(int y = -1; y <2;y++ ){
    for(int x = -1; x < 2; x++){
      if((y+r) < 0 || (y+r) >= m_yDim ){
        continue;
      }
      if((x+c)<0 || (x+c) >= m_xDim){

        continue;
      }
      if(m_board[y+r][x+c] == findMe){
        row = y + r;
        col = x + c;
        return true;
      }
    }
  }
  return false;
}



//will remove the prey from the vector.
//Returns the prey's health
//Or -1 if it couldn't be found.
int Board::removePrey(int row, int col){
  int health;
  for(int i =0; i < m_prey.size(); i++){
    //Found the prey, remove it
    if((m_prey[i].getRow() == row)&&(m_prey[i].getCol() == col)){
      health = m_prey[i].getHealth();
      m_prey.erase(m_prey.begin() + i);
      return health;
    }
  }
  cout<<"Error! Couldn't find the desired prey to remove!"<<endl;
  return -1;
}

int Board::numPrey(){
  return m_prey.size();
}

int Board::numPredators(){
  return m_predators.size();
}

void Board::overPopulation(int killAmount){
  //Want to kill more predators than prey, as it is easier for predators to be born.
  int kPredAmount = killAmount * .75;
  int kPreyAmount = killAmount * .25;
  bool breakWhile = false;
  int removeRow, removeCol,removeIndx;

  //Making sure we don't kill more of a creature than we have
  while(!breakWhile){
    breakWhile = true;
    if(kPreyAmount > m_prey.size()){
      kPreyAmount = kPreyAmount/2;
      breakWhile = false;
    }
    if(kPredAmount>m_predators.size()){
      kPredAmount = kPredAmount/2;
      breakWhile = false;
    }
  }

//Remove Predators
  for(int i = 0; i < kPredAmount; i++){
    removeIndx = rand() % m_predators.size();
    removeRow = m_predators[removeIndx].getRow();
    removeCol = m_predators[removeIndx].getCol();
    m_board[removeRow][removeCol] = 2;
    m_predators.erase(m_predators.begin()+removeIndx);
  }

//Remove Prey
  for(int i = 0; i < kPreyAmount; i++){
    removeIndx = rand() % m_prey.size();
    removeRow = m_prey[removeIndx].getRow();
    removeCol = m_prey[removeIndx].getCol();
    m_board[removeRow][removeCol] = 2;
    m_prey.erase(m_prey.begin()+removeIndx);
  }

  cout<<"Half of the creatures have been removed from the board due to overPopulation!"<<endl;

  //Ensure ther eare still a decent amount of prey on the board.
  if(numPrey() <= (m_xDim * m_yDim / 8)){
    while(numPrey() <= (m_xDim * m_yDim / 4)){
      addPredPrey(0,1);
    }
  }

  
}