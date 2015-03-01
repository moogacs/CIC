all: run

run: main.o lcf.o
	g++ main.o lcf.o -o run

main.o: main.cpp
	g++ -c main.cpp

lcf.o: lcf.cpp
	g++ -c lcf.cpp
clean:
	rm *o run
