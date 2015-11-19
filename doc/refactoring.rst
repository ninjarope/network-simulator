/rst
==============================
References to Design Decisions
==============================

http://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers
always references if you can

http://www.drbio.cornell.edu/pl47/programming/TICPP-2nd-ed-Vol-one-html/Chapter14.html
Composition vs. inheritance (revisited)

One of the clearest ways to determine whether you should be using composition or inheritance is by asking whether you’ll ever need to upcast from your new class. Earlier in this chapter, the Stack class was specialized using inheritance. However, chances are the StringStack objects will be used only as string containers and never upcast, so a more appropriate alternative is composition:

http://stackoverflow.com/questions/22700243/c-aggregation-inheritance-and-pointers
I think pointers are fine if you can be confident the data source and options source are alive during the lifetime of the algorithm. I don't think pointers are unavoidable though. Here are few other options (some of which are C++11):
...As long as you are clear about ownership, pointers are fine though.

http://stackoverflow.com/questions/10552719/is-it-acceptable-to-always-use-pointers-instead-of-references-to-be-easily-conv
If it's a reference, you don't need to worry about memory management, and that's the purpose of a smart pointer.

is there any way to quickly change a reference to pointer?
Yes, taking it's address (&).

/endrst
