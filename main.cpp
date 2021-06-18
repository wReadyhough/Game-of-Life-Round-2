#include "parent.h"



int main(){
  Predator myPredator;
  Prey myPrey;
  cout<<"A predator starts with a health of "<<myPredator.getHealth()<<endl;
  cout<<"A predator has a color of "<<myPredator.getColor()<<endl;
  cout<<"A prey starts with a health of "<<myPrey.getHealth()<<endl;
  cout<<"A prey starts with a color of "<<myPrey.getColor()<<endl;
  return 0;
}