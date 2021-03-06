//
//  Packet.h
//  NetworkSimulator

#ifndef __NetworkSimulator__Packet__
#define __NetworkSimulator__Packet__

#include "../ns.h"

/**
 * Packet that travels between nodes
 */
class Packet {
public:
    Packet();

    /** Construct packet that has source & destination addresses and some content (data).
        The amount of data defines packet size. */
    Packet(ns::AddressType s, ns::AddressType d, ns::PacketDataType data, double size = 1.0);

    //copy constructor
   Packet(const Packet& that) : id(that.id), destination(that.destination), data(that.data), size(that.size){}

   //copy assignment operator
   Packet& operator=(const Packet& that)
     {
         id = that.id;
         destination = that.destination;
         data = that.data;
         size = that.size;

         return *this;
     }

   //destructor
   ~Packet(){}

    /** Return packet ID. */
    ns::PacketIdType getID();

    /** Return source address. */
    ns::AddressType getSource();

    /** Return destination address. */
    ns::AddressType getDestination();

    /** Return packet contents. */
    ns::PacketDataType getData();

    /** Return size of the packet. */
    double getSize();

private:
    ns::PacketIdType id;
    ns::AddressType source, destination;
    ns::PacketDataType data;
    double size;
};

#endif /* defined(__NetworkSimulator__Packet__) */
