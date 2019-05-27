#include "Handlers.h"

Response* SignupHandler::callback(Request* req) {
	Map body = req->getBodyMap();
    if (body["username"] == "root")
        throw Server::Exception("Remote root access has been disabled.");
    cout << "username: " << body["username"] << ",\tpassword: " << body["password"] << endl;
	Response* res = Response::redirect("/");
    // res->setSessionId("SID");
    return res;
}
