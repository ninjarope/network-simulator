# Network Simulator

Simulator for network connection points, paths between them and packets flowing in midst of this all.

## Quick summary of w46

### Network

Network has function which returns pointers to all links / nodes in network 
+ in the newest version NetworkSimulator there is a Network (and Timer)

+ Also specific node by address

    network.getNode("some address")

### Node

A Node has a queue of Applications, which are activated for the receives and sends every clock cycle (receiving queue is consumed by the first application)

### Application

Application serve as a base class for Application logic / in other words for Routers, PacketGenerators (spew random packets) etc.

### Link

Links are composed of a pair of two nodes = pair<Node *, Node *>
+ Links could probably have same address or id too so that they could be accessed in same manner 

### Testing

main.cpp demonstrates current way of use


## Documentation

Included in the root folder are two doxygen configuration files that can be invoked by
    
    doxygen <doxygen-conf-file>

This will create documentation in html by default of the classes and their related material

### Requirements for the documentation

Doxygen - of course - to generate the documentation with it. This is the only requirement, if the non-graphs configuration is used.

The directory ./doc might be necessary to create by hand, if doxygen doesn't handle directory creation for you.
    
Graphviz should be installed to use doxygen with the graph enabled configuration. The graphs are built with graphviz's dot tool.

### Commenting for the documentation

Doxygen understands many variations of commenting. We should use these conventions:

    /**
     * Block comments for longer comments (classes etc)
     */

    /** one liners, that should be included in the doxygen */

    /* one liners that are only for code reading / no doxygen support */

    // same as the above (one liners)
## Directory structure

This repository contains three subdirectories:

* plan/ for the plan 
* doc/  for the final documentation
* src/  for all the source code


## Collaborators

Agrasagar Bhattacharyya
Chamran Moradi Ashour
Joni Turunen
Tommi Gröhn
