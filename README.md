# Network Simulator

Simulator for network connection points, paths between them and packets flowing in midst of this all. The approach of the implementation is somewhat top-level and statistics oriented.

---

## Usage

+ Build with make (Makefile included and should handle most platforms)
>
> Running the executive:
>
>```
>./ns [relative-xml-file-path]
>```

+ Shows a gui that has few keys mapped and mouse controls. Runs a 10s elapse by default.
+ To modify the network, use xml files (resources directory).
>
>Basic xml layout:
>
>```xml
><network>
>    <node address="somename" x="1.0" y="1.0">
>        <application type="PacketReceiver"/>
>        <application type="PacketGenerator"/>
>           <destination address="A"/>
>           ... more destinations ...
>        
>        ... more applications ...
>
>    </node>
>
>    ... more nodes ...
>
>    <link source="A" destination="B" directed="false" type="Wireless" speed="1.0" delay="1.0" weight="1.0"/>
>    
>    ... more links ...
>
></network>
>```
>
+ Applications to be used are 
    + PacketReceiver
    + PacketGenerator - defines the destinations for the generated packets
    + RandomRouter
    + TestRouter
+ Routing can be done with 
    + the random applications
    + with aforementioned links (xml) between nodes.
    + few implemented path algorithms (Currently only shortest path is implemented)
        + This requires tweeking of the code

---

## Architecture

### NetworkSimulator

+ Control layer for the program.
+ The NetworkSimulator inherits a Network and a Timer thus enclosing their functionality.

#### Network

+ Network has function which returns pointers to all links / nodes in network
>
>Example of getting a specific node by address:
>
>```
>network.getNode("some address")
>```
>

#### Timer

+ Clocks the processes in the program.
+ Can be paused.

### Node

+ Abstract layer for the nodes (mainly the ApplicationNode)

#### ApplicationNode

+ An ApplicationNode (subclass of Node) has a vector of Applications, which are activated for the receives and sends every clock cycle. Applications process host node's packet queue by reference, so the order of the applications is crucial.

### Application

+ Application serve as a base class for Application logic / in other words for Routers, PacketGenerators (spew random packets) etc.

#### ApplicationFactory

+ ApplicationFactory can be used for spawning concrete implementations of the Application class.

### Link

+ Links are composed of a pair of two nodes = pair<Node *, Node *>.

+ The simplest link type is a directed link, but undirected or bidirectional links are implicit in current implementations. They are implemented by having two directed links.

#### ParametricLink

+ Links have source and address. They also enclose parameters for speed, delay and weight to simulate bandwidth, latency and other such factors.

## Testing

+ Uses [Catch](https://github.com/philsquared/Catch) testing framework

+ Basic usage is through arguments. The executive can be run normally by not giving it any parameters. Parameters override the executive to be utilized for testing.
>
>Running tests for xml (linux):
>
>```
>./ns -n xml
>```
>
>./ns refers to the built executive. The parameters -n and xml refer to 'name' and the tag of the test. To get tags for all tests use:
>
>```
>./ns -l
>```
>
>and for help and usage:
>
>```
>./ns -h
>```
>
---

## Documentation

+ Included in the root folder are two doxygen configuration files. 
>
>Doxygen documentation can be generated with these configuration by running:
>
>```    
>   doxygen <doxygen-conf-file>
>```

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

---

## Directory structure

This repository contains three subdirectories:

+ plan/ for the plan 
+ doc/  for the final documentation
+ src/  for all the source code

---

## License

MIT license applies for all that's included here, if not explicitly stated otherwise (in files). See LICENSE.

---

## Team

Agrasagar Bhattacharyya
Chamran Moradi Ashour
Joni Turunen
Tommi Gröhn
