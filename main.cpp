#include "parent.h"



int main(){
  srand(time(NULL));
  int rows = 10, cols = 10, numPred = 6, numPrey = 8;
  cout<<"Making board with "<<rows<<" rows, "<<cols<<" cols, "<<numPred<<" predators, and "<<numPrey<<" prey."<<endl;
  Board theBoard(rows, cols, numPred, numPrey);
  theBoard.printBoard();
  while(theBoard.numPrey() > 0 && theBoard.numPredators() > 0){
    usleep(2000000);
    system("clear");
    cout<<"Updating board..."<<endl;
    theBoard.update();
    cout<<"Board looks like: "<<endl;
    theBoard.printBoard();
    
  }


  

  return 0;
}

/*while(theBoard.numPrey() > 0 && theBoard.numPreys() > 0){
    //usleep(1000000);
    //cin.get();
    cout<<"printing..."<<endl;
    theBoard.printBoard();
    cout<<"\n\n\n\n";
    cout<<"Updating..."<<endl;
    theBoard.update();
  }*/