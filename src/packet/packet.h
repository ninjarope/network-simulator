#ifndef _PACKET_H_
#define _PACKET_H_

#include <string>

class packet
{

public:
  packet();
  packet(int sourceNode, int destinationNode);
  packet(int sourceNode,int destinationNode,int maxHopCount);
  //test constructor with packet id and size
  packet(int sourceNode,int destination,int maxHopCount, std::string packet_id, int packet_size);
  int getSourceNode();
  int getDestintionNode();
  int getMaxHopCount();
  int getPacket_size();
  //to be made random and added function to check unique random
  std::string getPacket_id();
  //test function
  int showDetails();

private:
  int sourceNode;
  int destinationNode;
  int maxHopCount;
  std::string packet_id;
  int packet_size;

};

#endif
