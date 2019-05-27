#include "Handlers.h"

Response* StartHandler::callback(Request* req) {
	Response* res = Response::redirect("/login");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* SignupHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();

	UserRepository::userRepository->addUser(body);
	
	Response* res = Response::redirect("/login");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* LoginHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();

	UserRepository::userRepository->login(body);
	
	Response* res = Response::redirect("/signup");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* LogoutHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	
	UserRepository::userRepository->logoutCurrentUser();
	
	Response* res = Response::redirect("/login");
	res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
	return res;
}

Response* AddFilmHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();
	
	UserRepository::userRepository->getCurrentUser()->postFilm(body);
	
	Response* res = Response::redirect("/login");
	return res;
}
