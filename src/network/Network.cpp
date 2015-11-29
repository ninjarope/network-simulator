//
//  Network.cpp
//  NetworkSimulator
//
//  Created by Tommi Gröhn on 13.11.2015.
//  Copyright (c) 2015 tommigrohn. All rights reserved.
//
#include "Network.h"
Network::Network() { }
Network::~Network() {
  for (auto &link : links) delete link;
  for (auto &node : nodes) delete node.second;
}
const std::map<ns::AddressType, ApplicationNode *> &Network::getNodes() const { return nodes; }
const std::vector<Link *> &Network::getLinks() const { return links; }
ApplicationNode *Network::operator[](ns::AddressType address) const {
  return getNode(address);
}
ApplicationNode *Network::getNode(ns::AddressType address) const {
  if (nodes.at(address))
    return nodes.at(address);
  else
    return nullptr;
}
const Link *Network::getLink(ns::AddressType source, ns::AddressType destination) const {
  // TODO: exception handling
  /** \todo { exception handling } */
  for (auto &link : links) {
    if (link->getDestination()->getAddress() == destination) return link;
  }
  return nullptr;
}
bool Network::addNode(ns::AddressType address) {
  nodes.insert({address, new ApplicationNode(address)});
  addresses.push_back(address);
  return true;
}
bool Network::addLink(ns::AddressType source, ns::AddressType destination, Link *l) {
  // TODO: exception handling
  /** \todo { exception handling } */
  if (l) {
    this->allAvailableLinks.insert({source, destination});
    this->allAvailableLinks.insert({destination, source});
    l->setSource(this->getNode(source));
    l->setDestination(this->getNode(destination));
    links.push_back(l);
    return true;
  } else return false;
}
bool Network::addLink(ns::AddressType source, ns::AddressType destination, double weight, Link* l) {
    if (addLink(source, destination, l)) {
        this->allAvailableLinks.insert({source, destination});
        this->allAvailableLinks.insert({destination, source});
        l->setWeight(weight);
        return true;
    } else return false;
}
bool Network::removeNode(ns::AddressType address) {

  auto it = addresses.begin();
  while (it != addresses.end()) {
    if (*it == address) {
      addresses.erase(it);
      break;
    } else it++;
  }
  /* Erase bad links. */
  for (auto &l : links) {
    ns::AddressType destination = l->getDestination()->getAddress();
    if (destination == address) {
      removeLink(l->getSource()->getAddress(), address);
    }
  }
  delete nodes.at(address);
  nodes.erase(address);
  return true;
}
bool Network::removeLink(ns::AddressType source, ns::AddressType destination) {
  bool b = false;
  // Removing the link from the storage
  for (auto itr = this->allAvailableLinks.begin(); itr != this->allAvailableLinks.end(); itr++) {
    if ((itr->first == source && itr->second == destination) || (itr->first == destination && itr-> second == source)) {
    this->allAvailableLinks.erase(itr);
    }
  }
  auto it = links.begin();
  for (auto &l : links) {
    ns::AddressType src = l->getSource()->getAddress();
    ns::AddressType dest = l->getDestination()->getAddress();
    if ((src == source && dest == destination) || (src == destination && dest == source)) {
      delete l;
      links.erase(it);
      b = true;
    }
    it++;
  }
  return b;
}
size_t Network::getNodeCount() {
  return nodes.size();
}
size_t Network::getLinkCount() {
  return links.size();
}
const std::vector<ns::AddressType> &Network::getAddresses() const {
  return addresses;
}
/** check LinkStorage */
/*void Network::printLinks(){
  for (auto i : this->allAvailableLinks){
    std::cout << i.first << "-" << i.second << std::endl;
  }
}*/
