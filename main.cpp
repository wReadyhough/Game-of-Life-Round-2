#include "parent.h"



int main(){
  srand(time(NULL));
  int rows = 20, cols = 20, numPred = 20, numPrey = 20;
  cout<<"Making board with "<<rows<<" rows, "<<cols<<" cols, "<<numPred<<" predators, and "<<numPrey<<" prey."<<endl;
  Board theBoard(rows, cols, numPred, numPrey);
  theBoard.printBoard();
  while(theBoard.numPrey() > 0 && theBoard.numPredators() > 0){
    usleep(1000000);
    system("clear");
    cout<<"Updating board..."<<endl;
    theBoard.update();
    cout<<"Board looks like: "<<endl;
    theBoard.printBoard();
    
  }


  

  return 0;
}

