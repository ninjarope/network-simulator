#ifndef NODE_H
#define NODE_H
#include <iostream>
enum NodeType {
  ROUTER,
  END_HOST
};
enum AppType {
  SEND,
  RECEIVE,
  SEND_RECEIVE
};

class node {
public:
    Node();
    Node(int nodeAddr, NodeType nodeType, int nodeCapacity);
    int getAddress();
    std::vector<Application> getApplication ();
    bool nodeCapacity();
    void addNeighbor(Node* node);
    void send(int dest);
    void receive(Packet* packet);
    void checkNodeType();
    void checkAppType();

private:
NodeType nodeType;
int nodeCapacity;
int nodeAddress;
AppType appType;
bool checkNode;



};


#endif
