#include "Handlers.h"

Response* StartHandler::callback(Request* req) {
	Response* res = Response::redirect("/signup");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* SignupHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();

	UserRepository::userRepository->addUser(body);
	
	Response* res = Response::redirect("/home");
    res->setSessionId(intToString(UserRepository::userRepository->getCurrentUserId()));
    return res;
}

Response* LoginHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();

	UserRepository::userRepository->login(body);
	
	Response* res = Response::redirect("/home");
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
	
	Response* res = Response::redirect("/publisher");
	return res;
}

Response* AddMoneyHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map body = req->getBodyMap();

	UserRepository::userRepository->getCurrentUser()->addMoney(body);
	
	Response* res = Response::redirect("/profile");
	return res;
}

Response* BuyHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap();

	UserRepository::userRepository->getCurrentUser()->buyFilm(query);
	
	Response* res = Response::redirect("/film?film_id=" + query["film_id"]);
	return res;
}

Response* DeleteHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap();

	UserRepository::userRepository->getCurrentUser()->deleteFilm(query);
	
	Response* res = Response::redirect("/publisher");
	return res;
}

Response* RateHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap(), body = req->getBodyMap();
	body["film_id"] = query["film_id"];

	UserRepository::userRepository->getCurrentUser()->rateFilm(body);
	
	Response* res = Response::redirect("/film?film_id=" + query["film_id"]);
	return res;
}

Response* AddCommentHandler::callback(Request* req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap(), body = req->getBodyMap();
	body["film_id"] = query["film_id"];

	UserRepository::userRepository->getCurrentUser()->postComment(body);
	
	Response* res = Response::redirect("/film?film_id=" + query["film_id"]);
	return res;
}

ProfileHandler::ProfileHandler(string filePath) : TemplateHandler(filePath) {}
Map ProfileHandler::handle(Request *req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap();

	context["filmtables"] = makeHtmlOfFilms(UserRepository::userRepository->getCurrentUser()->findInPurchasedFilms(query));
	return context;
}

HomeHandler::HomeHandler(string filePath) : TemplateHandler(filePath) {}
Map HomeHandler::handle(Request *req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap();

	context["filmtables"] = makeHtmlOfFilms(UserRepository::userRepository->getCurrentUser()->findFilms(query));
	return context;
}

PublisherHandler::PublisherHandler(string filePath) : TemplateHandler(filePath) {}
Map PublisherHandler::handle(Request *req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap();

	context["filmtables"] = makeHtmlOfFilms(UserRepository::userRepository->getCurrentUser()->findInPublishedFilms(query), true, "delete");
	return context;
}

FilmHandler::FilmHandler(string filePath) : TemplateHandler(filePath) {}
Map FilmHandler::handle(Request *req) {
	UserRepository::userRepository->changeCurrentUserTo(stringToInt(req->getSessionId()));
	Map context, query = req->getQueryMap();
	int filmId = stringToInt(query["film_id"]);

	context["filmid"] = query["film_id"];
	context["filmtable"] = makeTableOfFilm(filmId, true, "buy");
	context["recommendedfilmtables"] = makeHtmlOfFilms(UserRepository::userRepository->getCurrentUser()->getRecommendedFilmIds(query), false);
	context["comments"] = makeHtmlOfcomments(FilmRepository::filmRepository->getFilmById(filmId)->getComments());
	return context;
}


string makeHtmlOfFilms(vector<int> ids, bool detailed, string linkType) {
	stringstream tables;
	for (int id : ids) {
		tables << makeTableOfFilm(id, detailed, linkType) << "<br>";
	}
	return tables.str();
}

string makeTableOfFilm(int id, bool detailed, string linkType) {
	Map data = FilmRepository::filmRepository->getFilmById(id)->getData();
	stringstream table;
	table
	<< " <br><div class='mui-panel'> "
	<< " <table class='mui-table mui-table--bordered'> "
	<< " 	<tr> "
	<< " 		<td colspan='2'> Name: <a href='film?film_id=" << id << "'> " << data["name"] << "</a> </td> "
	<< " 	</tr> "
	<< " 		<td> Director:" << data["director"] << " </td> "
	<< " 		<td> Length:" << data["length"] << " </td> "
	<< " 	</tr> "
	<< " 	<tr> ";
	if (detailed) {
		table
		<< "	<tr> "
		<< "		<td> Rate:" << data["rate"] << " </td> "
		<< "		<td> Year:" << data["year"] << " </td> "
		<< "	</tr> "
		<< "	<tr> "
		<< "		<td colspan='2'> Summary:" << data["summary"] << " </td> "
		<< "	</tr> "
		<< "	<tr> "
		<< "		<td> Price:" << data["price"] << " </td> "
		<< "        <td> <button class='mui-btn mui-btn--small mui-btn--primary' onclick=\"window.location.href='" << linkType << "?film_id=" << id << 
					"';\">" << (linkType == "film" ? "details" : linkType) << "</button> </td>"
		<< "	</tr> ";
	}
	table
	<< " </table> "
	<< " </div> ";
	return table.str();
}

string makeHtmlOfcomments(vector<string> comments) {
	stringstream div;
	div << "<div>";
	for (string comment : comments) {
		div << "<div class='mui-panel'>" <<  comment << "</div>";
	}
	div << "</div>";
	return div.str();
}