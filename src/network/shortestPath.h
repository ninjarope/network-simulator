#ifndef _SHORTESTPATH_H_
#define    _SHORTESTPATH_H_

#include <memory>

#include "../ns.h"
#include "Network.h"
#include "NetworkSimulator.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <vector>


class shortestPath{
public:
  shortestPath(std::map<ns::AddressType, ApplicationNode*> nodes ,std::vector<Link*> links);
  void permute (std::vector<std::string> allNodes);
  std::vector<std::string> allNodes;
  std::vector<Link*> allLinks;
  //std::vector< std::vector<std::string> > NodeRtable_fullpossiblepaths;
};
#endif
