.PHONY: all clean

all: test.out

test.out: use1.cpp coords.o
	g++ -o coords.o use1.cpp

coords.o: coords.h coords.cpp
	g++ -c coords.cpp

clean:
	rm -f *.o *.out *~ *.ghc
