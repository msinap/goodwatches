CC := g++ -std=c++11

all: a.out

a.out: main.o utility.o CommandManager.o UserRepository.o User.o Publisher.o FilmRepository.o Film.o
	$(CC) make/main.o make/utility.o make/CommandManager.o make/UserRepository.o make/User.o make/Publisher.o make/FilmRepository.o make/Film.o -o a.out

main.o: code/utility.h code/CommandManager.h code/main.cpp
	$(CC) -c code/main.cpp -o make/main.o

utility.o: code/utility.h code/utility.cpp
	$(CC) -c code/utility.cpp -o make/utility.o

CommandManager.o: code/utility.h code/UserRepository.h code/FilmRepository.h code/CommandManager.h code/CommandManager.cpp
	$(CC) -c code/CommandManager.cpp -o make/CommandManager.o

UserRepository.o: code/utility.h code/CommandManager.h code/User.h code/Publisher.h code/UserRepository.h code/UserRepository.cpp
	$(CC) -c code/UserRepository.cpp -o make/UserRepository.o

User.o: code/utility.h code/User.h code/User.cpp
	$(CC) -c code/User.cpp -o make/User.o

Publisher.o: code/utility.h code/User.h code/Publisher.h code/Publisher.cpp
	$(CC) -c code/Publisher.cpp -o make/Publisher.o

FilmRepository.o: code/utility.h code/CommandManager.h code/Film.h code/FilmRepository.h code/FilmRepository.cpp
	$(CC) -c code/FilmRepository.cpp -o make/FilmRepository.o

Film.o: code/utility.h code/CommandManager.h code/Film.h code/Film.cpp
	$(CC) -c code/Film.cpp -o make/Film.o

.PHONY: clean
clean:
	rm -r make/*.o
	rm a.out
