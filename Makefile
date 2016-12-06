all : cp cp2

cp : ClosestPair123.o Object.o
	g++ ClosestPair123.o Object.o -o cp

cp2 : ClosestPair124.o Object.o
	g++ ClosestPair124.o Object.o -o cp2

ClosestPair123.o : ./src/ClosestPair123.cpp ./src/Object.h
	g++ -c ./src/ClosestPair123.cpp

ClosestPair124.o : ./src/ClosestPair124.cpp ./src/Object.h
	g++ -c ./src/ClosestPair124.cpp

Object.o : ./src/Object.cpp ./src/Object.h
	g++ -c ./src/Object.cpp

clean :
	rm cp cp2 ClosestPair123.o ClosestPair124.o Object.o
