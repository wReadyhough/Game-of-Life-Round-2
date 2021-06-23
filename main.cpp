#include "parent.h"



int main(){
  srand(time(NULL));
  int rows = 5, cols = 5, numPred = 10, numPrey = 10;
  /*string defaults = "yes";
  cout<<"Do you want to use default values (yes or no): "<<endl;
  cin>>defaults;
  if(defaults!= "yes"){
    cout<<"# of rows: ";
    cin>>rows;
    cout<<"# of columns: ";
    cin>>cols;
    cout<<"# of predators: ";
    cin>>numPred;
    cout<<"# of prey: ";
    cin>>numPrey;
  }*/
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

