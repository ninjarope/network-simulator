# Network Simulator 

![Travis build status](https://travis-ci.org/ninjarope/network-simulator.svg?branch=master)

This page outlines the usage and architecture of the program while also instructing how to generate the doxygen api documentation. License and team information at the bottom.

---

This README among the other documentations and reports have been compiled and uploaded to a [temporary github page](http://rojun.github.io/doxygen_doc/index.html) (updated last in Dec 10, 2015 / commit 8ace..). We recommend to build/generate the doxygen documentation (instructions below) or following the given link.

---

## Dependencies

+ [SFML](http://www.sfml-dev.org/) for the gui

---

## Usage

+ Build with make (Makefile included and should handle at least linux and OSX)

 Running the executive:

```
./ns [relative-xml-file-path]
./ns [relative-xml-file-path] > log.txt
./ns random [node-count] [edge-count] [packet-generator-count]
```

#### Examples of running simulations:

Random

```
./ns random 50 50 10
./ns random 10 20 5
./ns random 1000 1000 100
```

XML specified

```
./ns resources/simple.xml
./ns resources/default.xml
./ns resources/large.xml
```

### Control and specifications

+ Shows a gui that has few keys mapped and mouse controls. Runs a 10s elapse by default.
+ Some of the controls work by holding alt and pressing mouse button on a node
+ To modify the network, use xml files (resources directory).

#### Examples of using the gui:

*Path, weights and total path weight if there's a route*

* Run the built executive file with defaults (just './ns')
* Click on a node
* Move mouse to another node

*Lock a destination* (in means of analysis: the routes, packet generators and paths still remain)

* Click another node

*Show queued traffic for the nodes* (links color in red according to the amount of traffic)

* Press M

*Show the queue for a node*

* Click on the two nodes sharing aforementioned red link

*Show traffic distribution*

* Press D

*Restart the simulation* (or the timer, rather)

* Press Enter


### Basic xml layout:

```xml
<network interval="10" slowdownrate="1.0" endTime="10000">
    <node address="somename" x="1.0" y="1.0">
        <application type="PacketReceiver"/>
        <application type="PacketGenerator"/>
           <destination address="A"/>
           ... more destinations ...
        
        ... more applications ...

    </node>

    ... more nodes ...

    <link source="A" destination="B" directed="false" type="Wireless" speed="1.0" delay="1.0" weight="1.0"/>
    
    ... more links ...

</network>
```

+ Network's parameters are optional
    + interval = ms for every step
    + slowdownrate = the bigger, the slower
    + endTime = end point for the intervals
+ Applications to be used are 
    + PacketReceiver
    + PacketGenerator - defines the destinations for the generated packets
    + RandomRouter - is random
    + RTableRouter - uses the nodes routing table
+ Routing can be done with 
    + the random applications
    + with aforementioned links (xml) between nodes.
    + few implemented path algorithms (Currently only shortest path is implemented)
        + This requires tweeking of the code

---

## Documentation

+ Included in the root folder are two doxygen configuration files. 

Doxygen documentation can be generated with these configuration by running:

    `doxygen <doxygen-conf-file>`

This will create documentation in html by default of the classes and their related material

### Temporary backup for the doxygen

We've [generated the documentation](http://rojun.github.io/doxygen_doc/index.html) for the time being. This might not be accurate for the current state of the project until we get around to automate building these artifacts and hosting them online appropriately.

### Requirements for the documentation

*With graphs*

Install Doxygen and Graphviz and use the included 'doxygen-with-graphs' conf-file. The graphs are built with graphviz's dot tool.

*Without graphs*

Install Doxygen and use the included 'doxygen-without-graphs' conf-file.

In both cases the directory ./doxygen_doc might be necessary to create by hand, if doxygen doesn't handle directory creation for you.

### Commenting for the documentation

Doxygen understands many variations of commenting. We should use these conventions:

    /**
     * Block comments for longer comments (classes etc)
     */

    /** one liners, that should be included in the doxygen */

    // one liners that are only for code reading / no doxygen support

---

## Architecture

This is a quick overlook of the components that make things run. A more detailed version can be found in the Doxygen generated API documentation.

Classes are intended to follow loose coupling principles where applicable. It follows MVC-model abstracting the view layer. There's few other view layers implemented, but they are mostly for testing purposes. 

Threading has been implemented with computing the node and link changes. Synchronization has been taken into account, though it is yet to be tested thoroughly. This separation from the main-thread enables the view layer to operate reactively even if the background tasks are slowed down. 

### NetworkSimulator

+ Control layer for the program.
+ The NetworkSimulator inherits a Network and a Timer thus enclosing their functionality.

#### Network

+ Network has function which returns pointers to all links / nodes in network

Example of getting a specific node by address:

    `network.getNode("some address")`

#### Timer

+ Clocks the processes in the program.
+ Can be paused.
+ Is run in a separate thread

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

### XMLReader

+ Handles the reading of xml documents for to generate the network. Based on the [tinyxml2](http://www.grinninglizard.com/tinyxml2/) library (included as a header).

---

## Testing

+ Uses [Catch](https://github.com/philsquared/Catch) testing framework (included as a header).

+ Basic usage is through arguments. The executive can be run normally by not giving it any parameters. Parameters override the executive to be utilized for testing.

Running tests for xml (linux):

```
./ns "[tag]" <options>
```

./ns refers to the built executive. The arguments include the tag of the test and options for the tests. 

List all tags:

```
./ns -l
```

Help and usage:

```
./ns -h
```

---

## Directory structure

This repository contains three subdirectories:

+ doc/   :: Additional documentation
+ fonts/ :: Included fonts used with the Gui
+ plan/  :: First plan
+ resources/    :: Resources for the executive - f.ex. the xml files.
+ src/   :: Source code
+ traffic_logs/ :: In program traffic logs get saved here

---

## License

MIT license applies for all that's included here, if not explicitly stated otherwise (in files). See LICENSE.

---

## Team Ninjarope

Tommi Gröhn & Joni Turunen

### Previous contributors 
#### (team before Dec 2015)

* Agrasagar Bhattacharyya
* Chamran Moradi Ashour
* Joni Turunen
* Tommi Gröhn
