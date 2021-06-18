#include "parent.h"

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

Predator::Predator(){
  setColor("Red");
  setHealth(START_PREDATOR_HEALTH);
}

Prey::Prey(){
  setColor("Green");
  setHealth(START_PREY_HEALTH);
}