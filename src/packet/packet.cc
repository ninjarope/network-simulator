#include "packet.h"
#include <iostream>

packet::packet(){
  this->source = 1; //first node
  this->destination = 10; //last node
  this->maxHopCount = 10;
}

packet::packet(int source,int destination){
  this->source = source;
  this->destination = destination;
  this->maxHopCount = 10;
}

packet::packet(int source, int destination, int maxHopCount){
  this->source = source;
  this->destination = destination;
  this->maxHopCount = maxHopCount;
}
//test function
int packet::showDetails(){
  std::cout <<this->destination<< this->maxHopCount<< this->source<< std::endl;
}
