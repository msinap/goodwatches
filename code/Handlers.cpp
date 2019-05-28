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

ProfileHandler::ProfileHandler(string filePath) : TemplateHandler(filePath) {}
Map ProfileHandler::handle(Request *req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	User* currentUser = UserRepository::userRepository->getCurrentUser();
	Map context, query = req->getQueryMap();

	context["filmtables"] = makeHtmlOfFilms(UserRepository::userRepository->getCurrentUser()->findInPurchasedFilms(query));
	return context;
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
