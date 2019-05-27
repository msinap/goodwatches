#include "MyServer.h"

MyServer::MyServer(int port) : Server(port) {
}

BadRequestError::BadRequestError()
	: MyServer::Exception("Bad Request") {
}

NotFoundError::NotFoundError() 
	: MyServer::Exception("Not Found") {
}

PermissionDeniedError::PermissionDeniedError()
	: MyServer::Exception("Permission Denied") {
}