CC := g++ -std=c++11

all: a.out

a.out: main.o utility.o CommandManager.o UserRepository.o User.o Publisher.o FilmRepository.o Film.o CommentRepository.o Comment.o NotificationsRepository.o Notifications.o Admin.o MyServer.o response.o request.o utilities.o server.o route.o template_parser.o Handlers.o
	$(CC) make/main.o make/utility.o make/CommandManager.o make/UserRepository.o make/User.o make/Publisher.o make/FilmRepository.o make/Film.o make/CommentRepository.o make/Comment.o make/NotificationsRepository.o make/Notifications.o make/Admin.o make/MyServer.o make/response.o make/request.o make/utilities.o make/server.o make/route.o make/template_parser.o make/Handlers.o -o a.out

main.o: server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp code/utility.h code/CommandManager.h code/main.cpp 
	$(CC) -c code/main.cpp -o make/main.o

utility.o: code/utility.h code/utility.cpp
	$(CC) -c code/utility.cpp -o make/utility.o

CommandManager.o: code/utility.h code/UserRepository.h code/FilmRepository.h code/CommandManager.h code/CommandManager.cpp
	$(CC) -c code/CommandManager.cpp -o make/CommandManager.o

UserRepository.o: code/utility.h code/User.h code/Publisher.h code/Admin.h code/UserRepository.h code/UserRepository.cpp
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

Admin.o: code/utility.h code/FilmRepository.h code/Admin.h code/Admin.cpp
	$(CC) -c code/Admin.cpp -o make/Admin.o

template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) -c utils/template_parser.cpp -o make/template_parser.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) -c utils/response.cpp -o make/response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) -c utils/request.cpp -o make/request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) -c utils/utilities.cpp -o make/utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) -c server/server.cpp -o make/server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c server/route.cpp -o make/route.o

MyServer.o: code/MyServer.h code/MyServer.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c code/MyServer.cpp -o make/MyServer.o

Handlers.o: code/Handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) -c code/Handlers.cpp -o make/Handlers.o

.PHONY: clean
clean:
	rm -r make/*.o
	rm a.out
