all : cp cp2

cp : ClosestPair123.o Object.o
	g++ ClosestPair123.o Object.o -o cp

cp2 : ClosestPair124.o Object.o
	g++ ClosestPair124.o Object.o -o cp2

ClosestPair123.o : ClosestPair123.cpp Object.h
	g++ -c ClosestPair123.cpp

ClosestPair124.o : ClosestPair124.cpp Object.h
	g++ -c ClosestPair124.cpp

Object.o : Object.cpp Object.h
	g++ -c Object.cpp

clean :
	rm cp cp2 ClosestPair123.o ClosestPair124.o Object.o
