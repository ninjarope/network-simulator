#ifndef _SHORTESTPATH_H_
#define    _SHORTESTPATH_H_
#include <memory>
#include <cfloat>
#include "../ns.h"
#include "Network.h"
#include "NetworkSimulator.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <vector>
class shortestPath{
public:
  shortestPath(std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links,ns::LinkStorage allAvailableLinks);
  void permute ();
  bool chckSimmilarPath(std::vector< std::vector<std::string> > NodeRtable_fullpossiblepaths, std::vector<std::string> cpyAllNodes);
  double getWeightOfEachPath(std::vector<std::string> path);
  void allShortestPaths();
  void creatMapForNodes();
  std::vector<std::string> validate(std::vector<std::string> cpyAllNodes);
  std::vector<std::string> allNodes;
  std::vector<Link*> allLinks;
  std::vector< std::vector<std::string> > NodeRtable_fullpossiblepaths;
  std::vector< std::vector<std::string> > shortestPATHS;
  std::map<ns::AddressType, ApplicationNode*> nodes;
  std::vector<Link*> links;
  ns::LinkStorage allAvailableLinks;
  double minWeight = DBL_MAX;
};
#endif
//
