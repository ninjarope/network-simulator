#ifndef _SHORTESTPATH_H_
#define    _SHORTESTPATH_H_
#include <cfloat>

#include "../ns.h"
#include "Network.h"
#include "NetworkSimulator.h"

class ShortestPath {
  public:
    ShortestPath(std::map<ns::AddressType, ApplicationNode*> nodes,
                 std::vector<Link*> links,
                 ns::LinkStorage allAvailableLinks);

    const std::vector <std::vector<std::string>>& getShortestPaths() const;

    void alsideperm();

    void nextPerm(std::vector <std::string> permCpyAllNodes, std::string nod);

    bool checkSimilarPath
        (std::vector <std::vector<std::string>> nodeRTableFullPaths, std::vector <std::string> cpyAllNodes);

    double getWeightOfEachPath(std::vector <std::string> path);

    void allShortestPaths();

    void createMapForNodes();

    std::vector <std::string> validate(std::vector <std::string> cpyAllNodes);

    std::vector <std::string> allNodes;

  private:
    std::vector<Link*> allLinks;
    std::vector <std::vector<std::string>> nodeRTableFullPaths;
    std::vector <std::vector<std::string>> shortestPaths;
    std::map<ns::AddressType, ApplicationNode*> nodes;
    std::vector<Link*> links;
    ns::LinkStorage allAvailableLinks;
    double minWeight = DBL_MAX;
};
#endif
//
