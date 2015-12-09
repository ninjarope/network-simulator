//
//  ShortestPath.cpp
//  NetworkSimulator
//

#include <memory>
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <vector>

#include "ShortestPath.h"
//TODO:now i am getting a list of all paths for each node still i need to calculate the
//shortest path on the basis of weights. So another function will be added.
ShortestPath::ShortestPath(std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links,ns::LinkStorage allAvailableLinks){
    this->allAvailableLinks = allAvailableLinks;
    this->nodes = nodes;
    this->links = links;

    for(auto key:this->nodes){
      // secluded nodes are not taken into cnsideration for finding shortest path
      auto it = allAvailableLinks.find(key.first);
      if (it != allAvailableLinks.end()){
          allNodes.push_back(key.first);
      }
    }
}

const std::vector< std::vector<std::string> >& ShortestPath::getShortestPaths() const {
    return shortestPaths;
}

void ShortestPath::alsideperm(){
  /*
  this function selects one node at a time and make combination of the rest of the nodes and sends the info to next perm
  eg: if we have nodes A B C D
  it will choose A
  make a combination of B C D and send to next perm
  note: it will keep on repeating this process until the chosen node is the last node in the graph
  i.e D for this example
  */
    std::vector<std::string> permCpyAllNodes;
    std::vector<std::string> tempermCpyAllNodes;
    std::string nod="";

    //do{

    for(auto val:this->allNodes){
        permCpyAllNodes.push_back(val);
    }
    for(auto i=0;i<this->allNodes.size();i++){
        nod=this->allNodes.at(i);
        for(auto j=0;j<permCpyAllNodes.size();j++){
            if(nod != permCpyAllNodes.at(j)){
                tempermCpyAllNodes.push_back(this->allNodes.at(j));
            }
        }
        this->nextPerm(tempermCpyAllNodes,nod);
        tempermCpyAllNodes.clear();
        //permCpyAllNodes.clear();
    }
    permCpyAllNodes.clear();

  //}while ( std::next_permutation(this->allNodes.begin(), this->allNodes.end()) );


    //Print out NodeRtable
    //Filling up 2 node links from available links
    for(auto val:this->allAvailableLinks){
        std::vector<std::string> temp;
        temp.push_back(val.first);
        temp.push_back(val.second);
        bool is_equal=this->checkSimilarPath(nodeRTableFullPaths,temp);
        if(is_equal==1){
            temp.clear();
        }
        else{
            nodeRTableFullPaths.push_back(temp);
            temp.clear();
        }
    }
    //rev
      std::vector<std::string> tempRev;
      std::vector< std::vector<std::string> > revNodeRTableFullPaths;
    for(auto val:this->nodeRTableFullPaths){
      std::vector<std::string> temp;
      for(auto val2 : val){
        temp.push_back(val2);
      }
        std::reverse(  temp.begin(),  temp.end());
        //check validity and fill up revNod
        bool is_equal=this->checkSimilarPath(nodeRTableFullPaths,temp);
        if(is_equal==1){
            temp.clear();
        }
        else{
            revNodeRTableFullPaths.push_back(temp);
            temp.clear();
        }
        //done revNod
      }
      //filling up Nodetable with rev node
      for(auto valVec:revNodeRTableFullPaths){
        this->nodeRTableFullPaths.push_back(valVec);
      }


    //Print out NodeRtable
    std::cout<<"-----------------ALL POSSIBLE PATHS----------------:"<<std::endl;
    std::cout<<nodeRTableFullPaths.size()<<std::endl;
    for(unsigned int i=0;i<this->nodeRTableFullPaths.size();i++){
        for(unsigned int j=0;j<nodeRTableFullPaths[i].size();j++){
            std::cout<<this->nodeRTableFullPaths[i][j];
        }
        std::cout<<std::endl;
    }

    this->allShortestPaths();
    this->createMapForNodes();

}
void ShortestPath::nextPerm (std::vector<std::string> permCpyAllNodes, std::string nod){
  /*
  This function works in the following steps
  it makes combination of all paths keeping nod common
    eg: taking last example
    chosen node A
    rest of the nodes B C D
    combinations
    A B C D
    A C B D
    A D C B
    ... etc
    and while doing this it will call validate and validate the paths as per our configured map

  */
    std::vector<std::string> revCpyAllNodes;
    std::vector<std::string> cpyAllNodes;
    std::string f=permCpyAllNodes.at(0);
    std::string l=permCpyAllNodes.at(permCpyAllNodes.size()-1);
    bool check = false;
    //permutation and valid paths
    while(permCpyAllNodes.size()!=0 && check == false){
      std::cout<<"permcpy"<<std::endl;
      std::cout<<"node is "<<nod<<std::endl;
      for(auto m:permCpyAllNodes){
        std::cout<<m;
      }
      std::cout<<"----------------"<<std::endl;

        if(permCpyAllNodes.size()==1){
            permCpyAllNodes.clear();
            permCpyAllNodes.push_back(f);
            permCpyAllNodes.push_back(l);
            check=true;
            std::cout<<"permcpy size 1"<<std::endl;
            std::cout<<"node is "<<nod<<std::endl;
            for(auto m:permCpyAllNodes){
              std::cout<<m;
            }
              std::cout<<"----------------"<<std::endl;
        }

      //  std::cout<<"////////////////////////////////////////////////////////"<<std::endl;
        std::cout<<"////////////////////////////////////////////////////////"<<std::endl;
        do
        {
            cpyAllNodes.push_back(nod);
            revCpyAllNodes.push_back(nod);
            //print allnodes
            for(auto i:permCpyAllNodes){
                cpyAllNodes.push_back(i);
                revCpyAllNodes.push_back(i);
            }
            std::reverse(revCpyAllNodes.begin(),revCpyAllNodes.end());
            for(auto t:cpyAllNodes){
              std::cout<<t;
            }
            std::cout<<std::endl;
            //std::cout<<"----------------REV CPY---------"<<std::endl;
            for(auto m:revCpyAllNodes){
              //std::cout<<m;
            }
            //std::cout<<std::endl;


            //validate all the paths and rev path
            for(int count =1;count <=2;count++){
            if(count==1){
              cpyAllNodes=this->validate(cpyAllNodes);

              if(!cpyAllNodes.empty()){
                  //eliminating simmilar paths
                  bool is_equal=this->checkSimilarPath(this->nodeRTableFullPaths,cpyAllNodes);
                  if(is_equal!=1){

                      this->nodeRTableFullPaths.push_back(cpyAllNodes);
                    }
                  }
                  cpyAllNodes.clear();
                }
              else{
                revCpyAllNodes=this->validate(revCpyAllNodes);

                if(!revCpyAllNodes.empty()){
                    //eliminating simmilar paths
                    bool is_equal=this->checkSimilarPath(this->nodeRTableFullPaths,revCpyAllNodes);
                    if(is_equal!=1){

                        this->nodeRTableFullPaths.push_back(revCpyAllNodes);
                      }
                    }
                    revCpyAllNodes.clear();

              }


          }

        }  while ( std::next_permutation(permCpyAllNodes.begin(), permCpyAllNodes.end()) );
      //  std::cout<<"////////////////////////////////////////////////////////"<<std::endl;
        std::cout<<"////////////////////////////////////////////////////////"<<std::endl;
        permCpyAllNodes.pop_back();
    }
}
// Validates the paths in the string vector with respect to all paths in the given network
std::vector<std::string> ShortestPath::validate(std::vector<std::string> cpyAllNodes){
    std::vector<std::string> print ;
    bool validLink = false;
    bool goOn = true;
    auto checkIt = cpyAllNodes.at(cpyAllNodes.size()-1);
    auto it=cpyAllNodes.begin();
    while(goOn){
        auto itsecond =it;
        if((*it) == checkIt){
            break;
        }
        if(it==cpyAllNodes.end()){
            break;
        }
        itsecond++;
        for(auto i:this->allAvailableLinks){
            if((*it) == i.first && (*itsecond)== i.second){
                validLink = true;
                it++;
                break;
            }
            else{
                validLink = false;
            }
        }
        if(validLink == false){
            it++;
            while(it!=cpyAllNodes.end()){
                cpyAllNodes.pop_back();
                goOn=false;
            }
        }
    }
    if(cpyAllNodes.size()==1){
        cpyAllNodes.clear();
    }
    return cpyAllNodes;
}
//checks for simmilar paths in the final NodeRtable array
bool ShortestPath::checkSimilarPath(std::vector< std::vector<std::string> > nodeRTableFullPaths, std::vector<std::string> cpyAllNodes){
    bool is_equal=0;
    for(unsigned int i=0;i<this->nodeRTableFullPaths.size();i++){
        if(this->nodeRTableFullPaths[i].size() == cpyAllNodes.size()){
            is_equal = std::equal ( this->nodeRTableFullPaths[i].begin(), this->nodeRTableFullPaths[i].end(), cpyAllNodes.begin());
        }
        if(is_equal==1){
            break;
        }
    }
    return is_equal;
}

// takes the vector of the nodes involved in the and returns the weight of the path
double ShortestPath::getWeightOfEachPath(std::vector<std::string> path){
    double weight = 0;
    for(unsigned int i=0;i<path.size();i++){
        if((i+1) < path.size()){
            for (auto z : this->links){
                std::string source = z->getSource()->getAddress();
                std::string destination = z->getDestination()->getAddress();
                if((source == path[i] && destination == path[i+1]) || (source == path[i+1] && destination == path[i])){
                    weight += z->getWeight();
                }
            }
        }
    }
    return weight;
}

//Creating the vector of all shortest paths for the whole network
void ShortestPath::allShortestPaths(){
    std::map<std::string, double> temp;
    this->minWeight = DBL_MAX;

    /*
    filling a temporary map
    key is the address of source and destination together value is DBL_MAX
    */

    for (int i = 0; i < this->nodeRTableFullPaths.size() ; i++){
        std::string srcDest="";
        srcDest += this->nodeRTableFullPaths[i][0];
        srcDest += this->nodeRTableFullPaths[i][this->nodeRTableFullPaths[i].size()-1];
        temp.insert({srcDest, this->minWeight});
    }

    /*
    changing the value of the temporary map to minimum one
    */

    for (int i = 0; i < this->nodeRTableFullPaths.size() ; i++){
        std::string srcDest="";
        srcDest += this->nodeRTableFullPaths[i][0];
        srcDest += this->nodeRTableFullPaths[i][this->nodeRTableFullPaths[i].size()-1];
        double weight = this->getWeightOfEachPath(this->nodeRTableFullPaths[i]);
        auto it = temp.find(srcDest);
        if (it != temp.end() && weight < it->second){
            it->second = weight;
        }
    }
    /*
    comparing the tem map and the all possible paths
    if the key (source and destination) is equal to the source and destination of the path
     and the value of the temp (minimum weight) is equal to the weight of the path
     then that path added to the vector of shortestPaths
    */
    for (int i = 0; i < this->nodeRTableFullPaths.size() ; i++){
        std::string srcDest="";
        srcDest += this->nodeRTableFullPaths[i][0];
        srcDest += this->nodeRTableFullPaths[i][this->nodeRTableFullPaths[i].size()-1];
        double weight = this->getWeightOfEachPath(this->nodeRTableFullPaths[i]);
        auto it = temp.find(srcDest);
        if (it != temp.end() && weight == it->second){
            this->shortestPaths.push_back(this->nodeRTableFullPaths[i]);
        }
    }
    //printing for test
    std::cout<<"----------------------ALL SHORTEST PATHS------------------"<<std::endl;
    std::cout<<this->shortestPaths.size()<<std::endl;
    for (int i = 0; i < this->shortestPaths.size() ; i++){
        std::cout << "Path: ";
        for (int j = 0; j < this->shortestPaths[i].size() ; j++){
            std::cout << this->shortestPaths[i][j];
        }
        std::cout << std::endl;
        std::cout  <<"Weight:  "<< this->getWeightOfEachPath(this->shortestPaths[i])<< std::endl;
        std::cout << std::endl;
    }
    //printing for test
    std::cout << "-----------------TEMP MAP-----------------------" << std::endl;
    for (auto t : temp){
        std::cout << "SOURCE AND DESTINATION: " ;
        for (auto j : t.first){
            std::cout << j;
        }
        std::cout <<"  WEIGHT OF THE PATH: " << t.second << std::endl;
    }
}

//fill a variable "routingTable" which every node has
void ShortestPath::createMapForNodes(){
    for (auto node: this->nodes){
        for(unsigned int i=0;i<this->shortestPaths.size();i++){
            if(node.first == this->shortestPaths[i][0]){
                std::string dest = this->shortestPaths[i][this->shortestPaths[i].size()-1];
                std::string nextHop = this->shortestPaths[i][1];
                node.second->getRoutingTable().insert({dest, {nextHop, 0.0}});
            }
        }
    }
    //printing the routing table for test
    std::cout << "---------------------------MAP----------------------------" << std::endl;
    for (auto node : this->nodes){
        for (auto z : node.second->getRoutingTable()){
            std::cout << node.first << ": " << std::endl;
            std::cout << "Destination: " << z.first << " NextHop: " << z.second.nextHop << std::endl;
        }
        std::cout << "*********----------------------------------------------------------------**********" << std::endl;
    }
}
