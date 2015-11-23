#include "shortestPath.h"

//TODO:now i am getting a list of all paths for each node still i need to calculate the
//shortest path on the basis of weights. So another function will be added.

shortestPath::shortestPath(std::map < ns::AddressType, ApplicationNode * > nodes, std::vector < Link * > links) {

}


void shortestPath::permute(std::vector <std::string> allNodes) {
    std::sort(this->allNodes.begin(), this->allNodes.end());

    while (std::next_permutation(this->allNodes.begin(), this->allNodes.end())) {
        //this->NodeRtable_fullpossiblepaths.push_back(this->allNodes);
    }
    //Print out NodeRtable
    //  for(unsigned int i=0;i<this->NodeRtable_fullpossiblepaths.size();i++){
    // for(unsigned int j=0;j<4;j++){
    //         std::cout<<this->NodeRtable_fullpossiblepaths[i][j];
    // }
    //std::cout<<std::endl;
    //}

}


//
