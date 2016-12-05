cp : ClosedPoint.o Object.o
	g++ ClosedPoint.o Object.o -o cp

ClosedPoint.o : ClosedPoint.cpp Object.h
	g++ -c ClosedPoint.cpp

Object.o : Object.cpp Object.h
	g++ -c Object.cpp

clean :
	rm cp ClosedPoint.o Object.o
