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
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	User* currentUser = UserRepository::userRepository->getCurrentUser();
	Map query = req->getQueryMap();

	Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
	stringstream body;
	body
	<< " <!DOCTYPE html> "
	<< " <html> "
	<< " 	<head> "
	<< "  		<link rel='stylesheet' href='filmtable.css'> "
	<< " 	</head> "
	<< " 	<body> "
	<< " 		<form action='/addmoney' target='_self' method='POST'> "
	<< " 			Increase Money : <br> <input type='number' name='amount' placeholder='Amount' required> <br> "
	<< " 			<input type='submit' value='Submit'> "
	<< " 			<input type='reset' value='Reset'> "
	<< " 			<br> "
	<< " 		</form> "
	<< " 		<form action='' target='_self' method='GET'> "
	<< " 			Filter : <br> <input type='text' name='director' placeholder='Director'> <br> "
	<< " 			<input type='submit' value='Submit'> "
	<< " 			<input type='reset' value='Reset'> "
	<< " 			<br> "
	<< " 		</form> "
	<< makeHtmlOfFilms(UserRepository::userRepository->getCurrentUser()->findFilms(query))
	<< " 		<a href='/signup' target='_self' title='Signup'> Signup </a> <br> "
	<< " 		<a href='/logout' target='_self' title='Logout'> Logout </a> <br> "
	<< " 	</body> "
	<< " </html> ";
	res->setBody(body.str());
	return res;
}

string makeHtmlOfFilms(vector<int> ids, bool detailed) {
	stringstream tables;
	for (int id : ids) {
		tables << makeTableOfFilm(id, detailed) << "<br>";
	}
	return tables.str();
}

string makeTableOfFilm(int id, bool detailed) {
	Map data = FilmRepository::filmRepository->getFilmById(id)->getData();
	stringstream table;
	table
	<< " 		<table style='width:50%'> "
	<< " 			<tr> "
	<< " 				<td colspan='2'> Name:" << data["name"] << "</td> "
	<< " 			</tr> "
	<< " 				<td> Director:" << data["director"] << " </td> "
	<< " 				<td> Length:" << data["length"] << " </td> "
	<< " 			</tr> "
	<< " 			<tr> ";
	if (detailed) {
		table
		<< " 			<tr> "
		<< " 				<td> Rate:" << data["rate"] << " </td> "
		<< " 				<td> Year:" << data["year"] << " </td> "
		<< " 			</tr> "
		<< " 			<tr> "
		<< " 				<td colspan='2'> Summary:" << data["summary"] << " </td> "
		<< " 			</tr> "
		<< " 			<tr> "
		<< " 				<td> Price:" << data["price"] << " </td> "
		<< " 				<td> BUY </td> "
		<< " 			</tr> "
		<< " 		</table> ";
	}
	return table.str();
}
