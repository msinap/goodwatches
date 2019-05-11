CC := g++ -std=c++11

all: a.out

a.out: main.o utility.o CommandManager.o User.o
	$(CC) make/main.o make/utility.o make/User.o make/CommandManager.o -o a.out

main.o: code/utility.h code/main.cpp
	$(CC) -c code/main.cpp -o make/main.o

utility.o: code/utility.h code/utility.cpp
	$(CC) -c code/utility.cpp -o make/utility.o

CommandManager.o: code/utility.h code/User.h code/CommandManager.h code/CommandManager.cpp
	$(CC) -c code/CommandManager.cpp -o make/CommandManager.o

User.o: code/utility.h code/User.h code/User.cpp
	$(CC) -c code/User.cpp -o make/User.o

.PHONY: clean
clean:
	rm -r make/*.o
	rm a.out
