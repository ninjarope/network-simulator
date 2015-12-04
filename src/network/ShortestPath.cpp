#include <memory>
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <vector>

#include "ShortestPath.h"
//TODO:now i am getting a list of all paths for each node still i need to calculate the
//shortest path on the basis of weights. So another function will be added.
ShortestPath::ShortestPath(std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links,ns::LinkStorage allAvailableLinks){
    allAvailableLinks = allAvailableLinks;
    nodes = nodes;
    links = links;
    for(auto key:nodes){
        allNodes.push_back(key.first);
    }
}

const std::vector<std::vector<std::string>>& ShortestPath::getShortestPaths() const {
    return shortestPaths;
}

void ShortestPath::alsideperm() {
    std::vector <std::string> permCpyAllNodes;
    std::vector <std::string> tempermCpyAllNodes;
    std::string nod = "";
    for (auto val : allNodes) {
        permCpyAllNodes.push_back(val);
    }
    for (unsigned int i = 0; i < allNodes.size(); i++) {
        nod = allNodes.at(i);
        for (unsigned int j = 0; j < permCpyAllNodes.size(); j++) {
            if (nod != permCpyAllNodes.at(j)) {
                tempermCpyAllNodes.push_back(allNodes.at(j));
            }
        }
        nextPerm(tempermCpyAllNodes, nod);
        tempermCpyAllNodes.clear();
    }
    //Print out NodeRtable
    std::cout << "-----------------ALL POSSIBLE PATHS----------------:" << std::endl;
    for (auto val:allAvailableLinks) {
        std::vector <std::string> temp;
        temp.push_back(val.first);
        temp.push_back(val.second);
        bool isEqual = checkSimilarPath(nodeRTableFullPaths, temp);
        if (isEqual == 1) {
            temp.clear();
        }
        else {
            nodeRTableFullPaths.push_back(temp);
            temp.clear();
        }
    }
    std::cout << nodeRTableFullPaths.size() << std::endl;
    for (unsigned int i = 0; i < nodeRTableFullPaths.size(); i++) {
        for (unsigned int j = 0; j < nodeRTableFullPaths[i].size(); j++) {
            std::cout << nodeRTableFullPaths[i][j];
        }
        std::cout << std::endl;
    }

    allShortestPaths();
    createMapForNodes();

}
void ShortestPath::nextPerm(std::vector <std::string> permCpyAllNodes, std::string nod) {
    std::vector <std::string> cpyAllNodes;
    std::string f = permCpyAllNodes.at(0);
    std::string l = permCpyAllNodes.at(permCpyAllNodes.size() - 1);
    bool check = false;
    //permutation and valid paths
    while (permCpyAllNodes.size() != 0 && check == false) {
        if (permCpyAllNodes.size() == 1) {
            permCpyAllNodes.clear();
            permCpyAllNodes.push_back(f);
            permCpyAllNodes.push_back(l);
            check = true;
        }
        do {
            cpyAllNodes.push_back(nod);
            //print allnodes
            for (auto i:permCpyAllNodes) {
                cpyAllNodes.push_back(i);
            }
            //validate all the paths
            cpyAllNodes = validate(cpyAllNodes);

            if (!cpyAllNodes.empty()) {
                //eliminating simmilar paths
                bool isEqual = checkSimilarPath(nodeRTableFullPaths, cpyAllNodes);
                if (isEqual != 1) {

                    nodeRTableFullPaths.push_back(cpyAllNodes);
                }
            }
            cpyAllNodes.clear();
        } while (std::next_permutation(permCpyAllNodes.begin(), permCpyAllNodes.end()));
        permCpyAllNodes.pop_back();
    }
}
// Validates the paths in the string vector with respect to all paths in the given network
std::vector <std::string> ShortestPath::validate(std::vector <std::string> cpyAllNodes) {
    std::vector <std::string> print;
    bool validLink = false;
    bool goOn = true;
    auto checkIt = cpyAllNodes.at(cpyAllNodes.size() - 1);
    auto it = cpyAllNodes.begin();
    while (goOn) {
        auto itsecond = it;
        if ((*it) == checkIt) {
            break;
        }
        if (it == cpyAllNodes.end()) {
            break;
        }
        itsecond++;
        for (auto i:allAvailableLinks) {
            if ((*it) == i.first && (*itsecond) == i.second) {
                validLink = true;
                it++;
                break;
            }
            else {
                validLink = false;
            }
        }
        if (validLink == false) {
            it++;
            while (it != cpyAllNodes.end()) {
                cpyAllNodes.pop_back();
                goOn = false;
            }
        }
    }
    if (cpyAllNodes.size() == 1) {
        cpyAllNodes.clear();
    }
    return cpyAllNodes;
}
//checks for simmilar paths in the final NodeRtable array
bool ShortestPath::checkSimilarPath(std::vector <std::vector<std::string>> nodeRTableFullPaths,
                                    std::vector <std::string> cpyAllNodes) {
    bool isEqual = false;
    for (unsigned int i = 0; i < nodeRTableFullPaths.size(); i++) {
        if (nodeRTableFullPaths[i].size() == cpyAllNodes.size()) {
            isEqual = std::equal(nodeRTableFullPaths[i].begin(), nodeRTableFullPaths[i].end(), cpyAllNodes.begin());
        }
        if (isEqual) {
            break;
        }
    }
    return isEqual;
}

double ShortestPath::getWeightOfEachPath(std::vector <std::string> path) {
    double weight = 0;
    for (unsigned int i = 0; i < path.size(); i++) {
        if ((i + 1) < path.size()) {
            for (auto z : links) {
                std::string source = z->getSource()->getAddress();
                std::string destination = z->getDestination()->getAddress();
                if ((source == path[i] && destination == path[i + 1])
                    || (source == path[i + 1] && destination == path[i])) {
                    weight += z->getWeight();
                }
            }
        }
    }
    return weight;
}

void ShortestPath::allShortestPaths() {
    std::map<std::string, double> temp;
    minWeight = DBL_MAX;
    for (unsigned int i = 0; i < nodeRTableFullPaths.size(); i++) {
        std::string srcDest = "";
        srcDest += nodeRTableFullPaths[i][0];
        srcDest += nodeRTableFullPaths[i][nodeRTableFullPaths[i].size() - 1];
        temp.insert({srcDest, minWeight});
    }
    for (unsigned int i = 0; i < nodeRTableFullPaths.size(); i++) {
        std::string srcDest = "";
        srcDest += nodeRTableFullPaths[i][0];
        srcDest += nodeRTableFullPaths[i][nodeRTableFullPaths[i].size() - 1];
        double weight = getWeightOfEachPath(nodeRTableFullPaths[i]);
        auto it = temp.find(srcDest);
        if (it != temp.end() && weight < it->second) {
            it->second = weight;
        }
    }
    for (unsigned int i = 0; i < nodeRTableFullPaths.size(); i++) {
        std::string srcDest = "";
        srcDest += nodeRTableFullPaths[i][0];
        srcDest += nodeRTableFullPaths[i][nodeRTableFullPaths[i].size() - 1];
        double weight = getWeightOfEachPath(nodeRTableFullPaths[i]);
        auto it = temp.find(srcDest);
        if (it != temp.end() && weight == it->second) {
            shortestPaths.push_back(nodeRTableFullPaths[i]);
        }
    }
    std::cout << "----------------------ALL SHORTEST PATHS------------------" << std::endl;
    std::cout << shortestPaths.size() << std::endl;
    for (unsigned int i = 0; i < shortestPaths.size(); i++) {
        std::cout << "Path: ";
        for (unsigned int j = 0; j < shortestPaths[i].size(); j++) {
            std::cout << shortestPaths[i][j];
        }
        std::cout << std::endl;
        std::cout << "Weight:  " << getWeightOfEachPath(shortestPaths[i]) << std::endl;
        std::cout << std::endl;
    }
    std::cout << "-----------------TEMP MAP-----------------------" << std::endl;
    for (auto t : temp) {
        std::cout << "SOURCE AND DESTINATION: ";
        for (auto j : t.first) {
            std::cout << j;
        }
        std::cout << "  WEIGHT OF THE PATH: " << t.second << std::endl;
    }
}

void ShortestPath::createMapForNodes() {
    for (auto node: nodes) {
        for (unsigned int i = 0; i < shortestPaths.size(); i++) {
            if (node.first == shortestPaths[i][0]) {
                std::string dest = shortestPaths[i][shortestPaths[i].size() - 1];
                std::string nextHop = shortestPaths[i][1];
                node.second->getRoutingTable().insert({dest, nextHop});
            }
        }
    }
    std::cout << "---------------------------MAP----------------------------" << std::endl;
    for (auto node : nodes) {
        for (auto z : node.second->getRoutingTable()) {
            std::cout << node.first << ": " << std::endl;
            std::cout << "Destination: " << z.first << " NextHop: " << z.second << std::endl;
        }
        std::cout << "*********----------------------------------------------------------------**********" << std::endl;
    }
}

