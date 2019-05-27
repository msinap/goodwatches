#include "Handlers.h"

Response* SignupHandler::callback(Request* req) {
	Map body = req->getBodyMap();
	int sessionId = stringToInt(req->getSessionId());
	UserRepository::userRepository->changeCurrentUserTo(sessionId);
	Response* res = Response::redirect("/");
    res->setSessionId("SID");
    return res;
}
