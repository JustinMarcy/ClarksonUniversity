.PHONY: all clean

all:  use1.out


use1.out: circle.o shape.o rectangle.o use1.cpp
	g++ -o use1.out circle.o shape.o rectangle.o use1.cpp

rectangle.o: rectangle.h rectangle.cpp shape.o
	g++ -c rectangle.cpp

circle.o: circle.h circle.cpp shape.o
	g++ -c  circle.cpp 

shape.o: shape.h shape.cpp	
	g++ -c shape.cpp 

clean:
	rm -f *.o *.out *~ *.gch


