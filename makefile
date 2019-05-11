CC := g++ -std=c++11

all: a.out

a.out: main.o utility.o
	$(CC) make/main.o make/utility.o -o a.out

main.o: code/utility.h code/main.cpp
	$(CC) -c code/main.cpp -o make/main.o

utility.o: code/utility.h code/utility.cpp
	$(CC) -c code/utility.cpp -o make/utility.o


.PHONY: clean
clean:
	rm -r make/*.o
	rm a.out
