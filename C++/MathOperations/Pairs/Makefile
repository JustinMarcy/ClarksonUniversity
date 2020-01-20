.PHONY: all clean

all: driverp2.out


driverp2.out: driverp2.cpp pair.o
	g++ -o driverp2.out driverp2.cpp pair.o

pair.o: pair.h pair.cpp
	g++ -c pair.cpp

clean:
	rm -f *.out *.o *.gch *~

