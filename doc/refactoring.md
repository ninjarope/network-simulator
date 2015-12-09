References to Design Decisions
==============================

## Pointers vs References

http://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers
always references if you can

    It seemed very hard to implement the modules with only references without too much confusion as pointers were everywhere. We decided to use reference for the network simulator when we could.

http://stackoverflow.com/questions/22700243/c-aggregation-inheritance-and-pointers
I think pointers are fine if you can be confident the data source and options source are alive during the lifetime of the algorithm. I don't think pointers are unavoidable though. Here are few other options (some of which are C++11):
...As long as you are clear about ownership, pointers are fine though.

    The ownership was quite clear with the MVC model and the models have vectors of pointers.

http://stackoverflow.com/questions/10552719/is-it-acceptable-to-always-use-pointers-instead-of-references-to-be-easily-conv
If it's a reference, you don't need to worry about memory management, and that's the purpose of a smart pointer.

    We used unique_pointers for single instances. IIRC the ui.

http://www.drbio.cornell.edu/pl47/programming/TICPP-2nd-ed-Vol-one-html/Chapter14.html
Composition vs. inheritance (revisited)

One of the clearest ways to determine whether you should be using composition or inheritance is by asking whether you’ll ever need to upcast from your new class. Earlier in this chapter, the Stack class was specialized using inheritance. However, chances are the StringStack objects will be used only as string containers and never upcast, so a more appropriate alternative is composition:

    We tried to approach the composition 'theorem', but as f.ex. network and timer classes were not to be used in any other way than what inheritance would make available, it seemed to be over engineering to make them compositional. Nodes and links on the other hand use the composition model (nodes in network, applications in nodes, links have nodes..) 

## Threads

Threads picked up from this [tutorial](https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/) and complemented with few chapters of 'Concurrency in Action'.

Lock guards seemed to be the safest and simplest option. Simple in this case means also safe, because we felt that we shouldn't dwelve too far with a subject so complicated.

## Application Factory

The user layer for applications required to share their intricasies for every object that used them. This seemed foolish as it opens up too much control and is hard to maintain when the number of applications grew. A factory seemed like a logical mid point.
