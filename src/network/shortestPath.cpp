#include "shortestPath.h"
//TODO:now i am getting a list of all paths for each node still i need to calculate the
//shortest path on the basis of weights. So another function will be added.
shortestPath::shortestPath(std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links,ns::LinkStorage allAvailableLinks){
  this->allAvailableLinks = allAvailableLinks;
  this->nodes = nodes;
  this->links = links;
  for(auto key:this->nodes){
    allNodes.push_back(key.first);
  }
  for(auto lin:this->allAvailableLinks){
    //std::cout<<"key: "<<lin.first<<"value: "<<lin.second<<std::endl;
  }
}
void shortestPath::permute () {
    std::vector<std::string> cpyAllNodes;
    std::vector<std::string> permCpyAllNodes;
    for(auto val:this->allNodes){
      permCpyAllNodes.push_back(val);
    }
    while(permCpyAllNodes.size()!=2){
    std::sort (permCpyAllNodes.begin(),permCpyAllNodes.end());
    do
      {
        //print allnodes
        //std::cout<<"allnodes after permutation:"<<std::endl;
        for(auto i:permCpyAllNodes){
          //std::cout<<i;
          cpyAllNodes.push_back(i);
        }
      //  std::cout<<std::endl;
          //validate all the paths
          cpyAllNodes=this->validate(cpyAllNodes);
          //std::cout<<"Printing cpyAllNodes:"<<std::endl;
          for(auto i:cpyAllNodes){
            //std::cout<<i;
          }
          //std::cout<<std::endl;
          if(cpyAllNodes.empty()){
            //std::cout<<"cpyAllNodes is empty"<<std::endl;
          }
          else{
          //  std::cout<<"Printing cpyAllNodes which gets in nodeRtable:"<<std::endl;
            for(auto i:cpyAllNodes){
              //std::cout<<i;
            }
            //std::cout<<this->NodeRtable_fullpossiblepaths.size()<<std::endl;
            //eliminating simmilar paths
            bool is_equal=this->chckSimmilarPath(NodeRtable_fullpossiblepaths,cpyAllNodes);
              //std::cout<<"value of is_equal: "<<is_equal<<std::endl;
              if(is_equal==1){
              }
              else{
                //std::cout<<std::endl;
                //std::cout<<"size: "<<cpyAllNodes.size()<<std::endl;
                //std::cout<<"------------------------------------------"<<std::endl;
                this->NodeRtable_fullpossiblepaths.push_back(cpyAllNodes);
              }
            //eliminating simmilar paths
        }
        cpyAllNodes.clear();
      }  while ( std::next_permutation(permCpyAllNodes.begin(), permCpyAllNodes.end()) );
      //std::cout<<permCpyAllNodes.size()<<std::endl;
      permCpyAllNodes.pop_back();
      //std::cout<<permCpyAllNodes.size()<<std::endl;
    }
      //Print out NodeRtable

        for(auto val:this->allAvailableLinks){

          cpyAllNodes.push_back(val.first);
          cpyAllNodes.push_back(val.second);
          bool is_equal=this->chckSimmilarPath(NodeRtable_fullpossiblepaths, cpyAllNodes);
          if(is_equal==1){
            cpyAllNodes.clear();
          }
          else{
            NodeRtable_fullpossiblepaths.push_back(cpyAllNodes);
            cpyAllNodes.clear();
          }
      }
      // Print Path with their weights
      std::cout<<"FINAL Vector:"<<std::endl;
        std::cout<<NodeRtable_fullpossiblepaths.size()<<std::endl;

        for (int i = 0; i < this->NodeRtable_fullpossiblepaths.size() ; i++){
          std::cout << "Path: ";
          for (int j = 0; j < this->NodeRtable_fullpossiblepaths[i].size() ; j++){
            std::cout << this->NodeRtable_fullpossiblepaths[i][j];
          }
          std::cout << std::endl;
          std::cout  <<"Weight:  "<< this->getWeightOfEachPath(NodeRtable_fullpossiblepaths[i])<< std::endl;
          std::cout << std::endl;
        }
this->allShortestPaths();
std::cout << "--------------------------MAP OF EACH NODE------------------------------" << std::endl;
this->creatMapForNodes();


      //calculation of shortest path according to the valid paths in NodeRtable
}
std::vector<std::string> shortestPath::validate(std::vector<std::string> cpyAllNodes){
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

bool shortestPath::chckSimmilarPath(std::vector< std::vector<std::string> > NodeRtable_fullpossiblepaths, std::vector<std::string> cpyAllNodes){
  bool is_equal=0;
  for(unsigned int i=0;i<this->NodeRtable_fullpossiblepaths.size();i++){
    if(this->NodeRtable_fullpossiblepaths[i].size() == cpyAllNodes.size()){
          is_equal = std::equal ( this->NodeRtable_fullpossiblepaths[i].begin(), this->NodeRtable_fullpossiblepaths[i].end(), cpyAllNodes.begin());
        }
          if(is_equal==1){
            break;
          }
    }
    return is_equal;
}

double shortestPath::getWeightOfEachPath(std::vector<std::string> path){
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

void shortestPath::allShortestPaths(){
  std::map<std::string, double> temp;
  this->minWeight = DBL_MAX;
  for (int i = 0; i < this->NodeRtable_fullpossiblepaths.size() ; i++){
    std::string srcDest="";
    srcDest += this->NodeRtable_fullpossiblepaths[i][0];
    srcDest += this->NodeRtable_fullpossiblepaths[i][this->NodeRtable_fullpossiblepaths[i].size()-1];
    temp.insert({srcDest, this->minWeight});
  }
  for (int i = 0; i < this->NodeRtable_fullpossiblepaths.size() ; i++){
      std::string srcDest="";
      srcDest += this->NodeRtable_fullpossiblepaths[i][0];
      srcDest += this->NodeRtable_fullpossiblepaths[i][this->NodeRtable_fullpossiblepaths[i].size()-1];
      double weight = this->getWeightOfEachPath(this->NodeRtable_fullpossiblepaths[i]);
      auto it = temp.find(srcDest);
      if (it != temp.end() && weight < it->second){
        it->second = weight;
      }
  }
  for (int i = 0; i < this->NodeRtable_fullpossiblepaths.size() ; i++){
    std::string srcDest="";
    srcDest += this->NodeRtable_fullpossiblepaths[i][0];
    srcDest += this->NodeRtable_fullpossiblepaths[i][this->NodeRtable_fullpossiblepaths[i].size()-1];
    double weight = this->getWeightOfEachPath(this->NodeRtable_fullpossiblepaths[i]);
    auto it = temp.find(srcDest);
    if (it != temp.end() && weight == it->second){
      this->shortestPATHS.push_back(this->NodeRtable_fullpossiblepaths[i]);
    }
  }
  std::cout<<"----------------------ALL SHORTEST PATHS------------------"<<std::endl;
  std::cout<<this->shortestPATHS.size()<<std::endl;
    for (int i = 0; i < this->shortestPATHS.size() ; i++){
      std::cout << "Path: ";
      for (int j = 0; j < this->shortestPATHS[i].size() ; j++){
        std::cout << this->shortestPATHS[i][j];
     }
     std::cout << std::endl;
      std::cout  <<"Weight:  "<< this->getWeightOfEachPath(this->shortestPATHS[i])<< std::endl;
      std::cout << std::endl;
    }
  std::cout << "-----------------TEMP MAP-----------------------" << std::endl;
  for (auto t : temp){
    std::cout << "SORCE AND DESTINATION: " ;
    for (auto j : t.first){
      std::cout << j;
    }
    std::cout <<"  WEIGHT OF THE PATH: " << t.second << std::endl;
  }
}

void shortestPath::creatMapForNodes(){
  for (auto node: this->nodes){
    for(unsigned int i=0;i<this->shortestPATHS.size();i++){
      if(node.first == this->shortestPATHS[i][0]){
        std::string dest = this->shortestPATHS[i][this->shortestPATHS[i].size()-1];
        std::string nextHop = this->shortestPATHS[i][1];
        node.second->routingTable.insert({dest, nextHop});
      }
    }
  }
  for (auto node : this->nodes){
    for (auto z : node.second->routingTable){
      std::cout << node.first << ": " << std::endl;
      std::cout << "Destination: " << z.first << " NextHop: " << z.second << std::endl;
    }
    std::cout << "*********----------------------------------------------------------------**********" << std::endl;
  }
}












//
