#ifndef _PACKET_H_
#define _PACKET_H_


class packet
{

public:
  packet();
  packet(int source, int destination);
  packet(int source,int destination,int maxHopCount);
  int showDetails();

private:
  int source;
  int destination;
  int maxHopCount;

};

#endif
