runApp: ns1.o
		./ns1
ns1.o: test1.o packet.o
		g++ test1.o -o ns1
test1.o: test1.cc packet.o
		g++ -c test1.cc
packet.o: packet/packet.cc packet/packet.h
		g++ -c  packet/packet.cc

clean:
	rm ns1 packet.o test1.o
