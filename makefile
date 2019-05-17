CC := g++ -std=c++11

all: a.out

a.out: main.o utility.o CommandManager.o UserRepository.o User.o Publisher.o FilmRepository.o Film.o CommentRepository.o Comment.o NotificationsRepository.o Notifications.o
	$(CC) make/main.o make/utility.o make/CommandManager.o make/UserRepository.o make/User.o make/Publisher.o make/FilmRepository.o make/Film.o make/CommentRepository.o make/Comment.o make/NotificationsRepository.o make/Notifications.o -o a.out

main.o: code/utility.h code/CommandManager.h code/main.cpp
	$(CC) -c code/main.cpp -o make/main.o

utility.o: code/utility.h code/utility.cpp
	$(CC) -c code/utility.cpp -o make/utility.o

CommandManager.o: code/utility.h code/UserRepository.h code/FilmRepository.h code/CommandManager.h code/CommandManager.cpp
	$(CC) -c code/CommandManager.cpp -o make/CommandManager.o

UserRepository.o: code/utility.h code/User.h code/Publisher.h code/UserRepository.h code/UserRepository.cpp
	$(CC) -c code/UserRepository.cpp -o make/UserRepository.o

User.o: code/utility.h code/User.h code/User.cpp
	$(CC) -c code/User.cpp -o make/User.o

Publisher.o: code/utility.h code/User.h code/Publisher.h code/Publisher.cpp
	$(CC) -c code/Publisher.cpp -o make/Publisher.o

FilmRepository.o: code/utility.h code/Film.h code/FilmRepository.h code/FilmRepository.cpp
	$(CC) -c code/FilmRepository.cpp -o make/FilmRepository.o

Film.o: code/utility.h code/CommentRepository.h code/Film.h code/Film.cpp
	$(CC) -c code/Film.cpp -o make/Film.o

CommentRepository.o: code/utility.h code/Comment.h code/CommentRepository.h code/CommentRepository.cpp
	$(CC) -c code/CommentRepository.cpp -o make/CommentRepository.o

Comment.o: code/utility.h code/Comment.h code/Comment.cpp
	$(CC) -c code/Comment.cpp -o make/Comment.o

NotificationsRepository.o: code/utility.h code/Notifications.h code/NotificationsRepository.h code/NotificationsRepository.cpp
	$(CC) -c code/NotificationsRepository.cpp -o make/NotificationsRepository.o

Notifications.o: code/utility.h code/Notifications.h code/Notifications.cpp
	$(CC) -c code/Notifications.cpp -o make/Notifications.o

.PHONY: clean
clean:
	rm -r make/*.o
	rm a.out
