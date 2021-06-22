#include "parent.h"



int main(){
  srand(time(NULL));
  int rows = 5, cols = 5, numPred = 6, numPrey = 8;
  cout<<"Making board with "<<rows<<" rows, "<<cols<<" cols, "<<numPred<<" predators, and "<<numPrey<<" prey."<<endl;
  Board theBoard(rows, cols, numPred, numPrey);
  cout<<"Board looks like: "<<endl;
  theBoard.printBoard();
  cout<<"Updating board..."<<endl;
  theBoard.update();
  theBoard.printBoard();
  


  

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