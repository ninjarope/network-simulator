# Network Simulator

Simulator for network connection points, paths between them and packets flowing in midst of this all.

## Directory structure

This repository contains three subdirectories:

* plan/ for the plan 
* doc/  for the final documentation
* src/  for all the source code

### Documentation

Included in the root folder are two doxygen configuration files that can be invoked by
    
    doxygen <doxygen-conf-file>

This will create documentation in html by default of the classes and their related material

#### Requirements for the documentation

Doxygen - of course - to generate the documentation with it. This is the only requirement, if the non-graphs configuration is used.

The directory ./doc might be necessary to create by hand, if doxygen doesn't handle directory creation for you.
    
Graphviz should be installed to use doxygen with the graph enabled configuration. The graphs are built with graphviz's dot tool.


## Collaborators

Agrasagar Bhattacharyya
Chamran Moradi Ashour
Joni Turunen
Tommi Gröhn
