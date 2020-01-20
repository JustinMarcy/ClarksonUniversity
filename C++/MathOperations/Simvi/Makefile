## simple makefile for myvec and a client/user

all: simvi.out

simvi.out: simvi.o driver1.cpp
	g++ -o simvi.out driver1.cpp simvi.o

simvi.o: simvi.h simvi.cpp	
	g++ -c simvi.cpp simvi.h

clean:
	rm -f *o *out *~ *gch


