#include "Handlers.h"

Response* SignupHandler::callback(Request* req) {
	Map body = req->getBodyMap();
	int sessionId = stringToInt(req->getSessionId());
	UserRepository::userRepository->changeCurrentUserTo(sessionId);
	UserRepository::userRepository->addUser(body);
	Response* res = Response::redirect("/signup");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
	cout << UserRepository::userRepository->getCurrentUserId() << endl;
    return res;
}
