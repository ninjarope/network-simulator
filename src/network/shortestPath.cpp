#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <vector>
#include <memory>

#include "../ns.h"
#include "Network.h"
#include "NetworkSimulator.h"

//TODO:now i am getting a list of all paths for each node still i need to calculate the
//shortest path on the basis of weights. So another function will be added.

std::string AllNodes[] = {"A","B","C","D","E"};
int length = sizeof(AllNodes)/sizeof(AllNodes[0]);

int AllNodess(  std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links){
  //TODO: making the Allnodes array for use in Permute
  return 0;
}
int Permute (ns::AddressType address) {


  std::string SelectedNode = address;
  std::string Nodes[length-1];
  int count = 0;
  for(int i=0;i<length;i++){
      if(AllNodes[i]!=SelectedNode){
          Nodes[count]=AllNodes[i];
          count++;
      }
  }
  std::vector<std::string> Fullpaths;
  std::vector< std::vector<std::string> > NodeRtable_fullpaths;
    std::sort (Nodes,Nodes+length-2);
    do {
            std::cout<<Nodes[0]<<Nodes[1]<<Nodes[2]<<Nodes[3]<<length<<std::endl;
          Fullpaths.push_back(SelectedNode);
          for(int j=0;j<length-1;j++){
            Fullpaths.push_back(Nodes[j]);
            std::cout<<"Node j= "<<Nodes[j];

          }
          std::cout<<" ------ ";
          std::cout<<Fullpaths[0]<<Fullpaths[1]<<Fullpaths[2]<<Fullpaths[3]<<Fullpaths[4]<<std::endl;
          NodeRtable_fullpaths.push_back(Fullpaths);
         Fullpaths.clear();
    } while ( std::next_permutation(Nodes,Nodes+length-2) );

    for(int i=0;i<5;i++){
    std::cout<<NodeRtable_fullpaths[1][i]<<std::endl;

    }

    //TODO: another function to add the shortest path and make the routingtable of
    //destination and nexthops and returning it.
    return 0;
}

//
