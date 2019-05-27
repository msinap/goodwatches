#include "Handlers.h"

Response* StartHandler::callback(Request* req) {
	Response* res = Response::redirect("/login");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* SignupHandler::callback(Request* req) {
	int sessionId = stringToInt(req->getSessionId());
	UserRepository::userRepository->changeCurrentUserTo(sessionId);
	Map body = req->getBodyMap();

	UserRepository::userRepository->addUser(body);
	
	Response* res = Response::redirect("/login");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* LoginHandler::callback(Request* req) {
	int sessionId = stringToInt(req->getSessionId());
	UserRepository::userRepository->changeCurrentUserTo(sessionId);
	Map body = req->getBodyMap();

	UserRepository::userRepository->login(body);
	
	Response* res = Response::redirect("/signup");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* LogoutHandler::callback(Request* req) {
	int sessionId = stringToInt(req->getSessionId());
	UserRepository::userRepository->changeCurrentUserTo(sessionId);
	
	UserRepository::userRepository->logoutCurrentUser();
	
	Response* res = Response::redirect("/login");
	res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
	return res;
}
