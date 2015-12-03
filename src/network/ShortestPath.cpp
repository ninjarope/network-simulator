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
        allNodes.push_back(key.first);
    }
}

const std::vector< std::vector<std::string> >& ShortestPath::getShortestPaths() const {
    return shortestPaths;
}

void ShortestPath::alsideperm(){
    std::vector<std::string> permCpyAllNodes;
    std::vector<std::string> tempermCpyAllNodes;
    std::string nod="";
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
    }
    //Print out NodeRtable
    std::cout<<"-----------------ALL POSSIBLE PATHS----------------:"<<std::endl;
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
    std::vector<std::string> cpyAllNodes;
    std::string f=permCpyAllNodes.at(0);
    std::string l=permCpyAllNodes.at(permCpyAllNodes.size()-1);
    bool check = false;
    //permutation and valid paths
    while(permCpyAllNodes.size()!=0 && check == false){
        if(permCpyAllNodes.size()==1){
            permCpyAllNodes.clear();
            permCpyAllNodes.push_back(f);
            permCpyAllNodes.push_back(l);
            check=true;
        }
        do
        {
            cpyAllNodes.push_back(nod);
            //print allnodes
            for(auto i:permCpyAllNodes){
                cpyAllNodes.push_back(i);
            }
            //validate all the paths
            cpyAllNodes=this->validate(cpyAllNodes);
            
            if(!cpyAllNodes.empty()){
                //eliminating simmilar paths
                bool is_equal=this->checkSimilarPath(this->nodeRTableFullPaths,cpyAllNodes);
                if(is_equal!=1){
                    
                    this->nodeRTableFullPaths.push_back(cpyAllNodes);
                }
            }
            cpyAllNodes.clear();
        }  while ( std::next_permutation(permCpyAllNodes.begin(), permCpyAllNodes.end()) );
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

void ShortestPath::allShortestPaths(){
    std::map<std::string, double> temp;
    this->minWeight = DBL_MAX;
    for (int i = 0; i < this->nodeRTableFullPaths.size() ; i++){
        std::string srcDest="";
        srcDest += this->nodeRTableFullPaths[i][0];
        srcDest += this->nodeRTableFullPaths[i][this->nodeRTableFullPaths[i].size()-1];
        temp.insert({srcDest, this->minWeight});
    }
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
    std::cout << "-----------------TEMP MAP-----------------------" << std::endl;
    for (auto t : temp){
        std::cout << "SOURCE AND DESTINATION: " ;
        for (auto j : t.first){
            std::cout << j;
        }
        std::cout <<"  WEIGHT OF THE PATH: " << t.second << std::endl;
    }
}

void ShortestPath::createMapForNodes(){
    for (auto node: this->nodes){
        for(unsigned int i=0;i<this->shortestPaths.size();i++){
            if(node.first == this->shortestPaths[i][0]){
                std::string dest = this->shortestPaths[i][this->shortestPaths[i].size()-1];
                std::string nextHop = this->shortestPaths[i][1];
                node.second->getRoutingTable().insert({dest, nextHop});
            }
        }
    }
    std::cout << "---------------------------MAP----------------------------" << std::endl;
    for (auto node : this->nodes){
        for (auto z : node.second->getRoutingTable()){
            std::cout << node.first << ": " << std::endl;
            std::cout << "Destination: " << z.first << " NextHop: " << z.second << std::endl;
        }
        std::cout << "*********----------------------------------------------------------------**********" << std::endl;
    }
}

