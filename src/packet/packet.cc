#include "packet.h"
#include <iostream>
#include "packet_interface.h"
packet::packet(){
  this->sourceNode = 1; //first node
  this->destinationNode = 10; //last node
  this->maxHopCount = 10;
}

packet::packet(int sourceNode,int destination){
  this->sourceNode = sourceNode;
  this->destinationNode = destinationNode;
  this->maxHopCount = 10;
  this->packet_id = "AAA";
  this->packet_size = 100;
}

packet::packet(int sourceNode, int destinationNode, int maxHopCount){
  this->sourceNode = sourceNode;
  this->destinationNode = destinationNode;
  this->maxHopCount = maxHopCount;
  this->packet_id = "AAA1";
  this->packet_size = 100;
}
packet::packet(int sourceNode,int destinationNode,int maxHopCount, std::string packet_id, int packet_size){
  this->sourceNode = sourceNode;
  this->destinationNode = destinationNode;
  this->maxHopCount = maxHopCount;
  this->packet_id = packet_id;
  this->packet_size = packet_size;
}

std::string packet::getPacket_id(){
  return this->packet_id;
}
int packet::getDestintionNode(){
  return this->destinationNode;
}

int packet::getSourceNode(){
  return this->sourceNode;
}

int packet::getMaxHopCount(){
  return this->maxHopCount;
}

int packet::getPacket_size(){
  return packet_size;
}
//test function
int packet::showDetails(){
  std::cout <<getPacket_id()<<getPacket_size()<< getSourceNode()<< getDestintionNode()<< std::endl;
}
