#include "packet/packet.cc"
#include <iostream>

int main(){
  packet packet1(1,2,10);
  packet1.showDetails();
  std::cout<<"Hi it is working"<<std::endl;
  return 0;
}
