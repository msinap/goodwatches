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

Response* AddMoneyHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();

	UserRepository::userRepository->getCurrentUser()->addMoney(body);
	
	Response* res = Response::redirect("/profile");
	return res;
}

Response* ProfileHandler::callback(Request* req) {
	Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
	stringstream body;
	body
	<< " <!DOCTYPE html> "
	<< " <html> "
	<< " 	<head> "
	<< "  "
	<< " 	</head> "
	<< " 	<body> "
	<< " 		<form action='/addmoney' target='_self' method='POST'> "
	<< " 			Increase Money : <br> <input type='number' name='amount' placeholder='Amount' required> <br> "
	<< " 			<input type='submit' value='Submit'> "
	<< " 			<input type='reset' value='Reset'> "
	<< " 			<br> "
	<< " 		</form> "
	<< " 		<a href='/signup' target='_self' title='Signup'> Signup </a> <br> "
	<< " 		<a href='/logout' target='_self' title='Logout'> Logout </a> <br> "
	<< " 	</body> "
	<< " </html> ";
	res->setBody(body.str());
	return res;
}
