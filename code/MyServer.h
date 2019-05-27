#ifndef MYSERVER_HPP
#define MYSERVER_HPP

#include "../server/server.hpp"

class MyServer : public Server {
public:
    MyServer(int port = 5000);
};

class BadRequestError : public MyServer::Exception {
public:
	BadRequestError();
};

class NotFoundError : public MyServer::Exception {
public:
	NotFoundError();
};

class PermissionDeniedError : public MyServer::Exception {
public:
	PermissionDeniedError();
};

#endif