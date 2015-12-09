//
//  ShortestPath.h
//  NetworkSimulator
//

#ifndef _SHORTESTPATH_H_
#define    _SHORTESTPATH_H_

#include <cfloat> // for DBL_MAX the greatest amount of a double used in finding shortest path

#include "../ns.h"
#include "../node/ApplicationNode.h"
#include "../link/Link.h"

class ShortestPath {
public:
    ShortestPath() = default;
    
    ShortestPath(std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links,ns::LinkStorage allAvailableLinks);

    const std::vector< std::vector<std::string> >& getShortestPaths() const;

    //does all possible permutations of paths for all sides of a node and sends it to next perm for finding out valid paths
    void alsideperm();
    //creates possible perrmutation for a node from 2 nodes to the total number of nodes
    void nextPerm(std::vector<std::string> permCpyAllNodes,std::string nod);
    //checks if simmilar path exists in the nodeRtableFullPaths
    bool checkSimilarPath(std::vector< std::vector<std::string> > nodeRTableFullPaths, std::vector<std::string> cpyAllNodes);

    // takes the vector of the nodes involved in the and returns the weight of the path
    double getWeightOfEachPath(std::vector<std::string> path);

    //derive the all SHORTEST paths available in the network from the all possible paths
    void allShortestPaths();

    //fill a variable "routingTable" which every node has
    void createMapForNodes();
    //checks validity of all the paths given in the parameter vector
    std::vector<std::string> validate(std::vector<std::string> cpyAllNodes);

    std::vector<std::string> allNodes;

private:
    std::vector<Link*> allLinks;
    std::vector< std::vector<std::string> > nodeRTableFullPaths;
    std::vector< std::vector<std::string> > shortestPaths;
    std::map<ns::AddressType, ApplicationNode*> nodes;
    std::vector<Link*> links;
    ns::LinkStorage allAvailableLinks;
    double minWeight = DBL_MAX;
};
#endif
//
