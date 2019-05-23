#include "User.h"
#include "UserRepository.h"
#include "FilmRepository.h"
#include "NotificationsRepository.h"
#include "Notifications.h"

User::User() 
	: id(-1), money(0) {
}

User::User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : data(parameters), id(_id), userRepository(ur), filmRepository(fr), notificationsRepository(new NotificationsRepository()), money(0) {
    checkMustHave({"email", "username", "password", "age"}, data);
    checkMayHave ({"email", "username", "password", "age", "publisher"}, data);
    checkEmail(parameters["email"]);
    if(userRepository->findUserWithUsername(data["username"]) != NULL)
        throw BadRequestError();
    checkNumeric(parameters["age"]);
	data["password"] = hashFletcherCRC(data["password"]);
}

void User::addMoney(Map &parameters) {
	checkMustHave({"amount"}, parameters);
	checkMayHave({"amount"}, parameters);
	money += stringToInt(parameters["amount"]);
}

void User::buyFilm(Map &parameters) {
	checkMustHave({"film_id"}, parameters);
	checkMayHave({"film_id"}, parameters);
	int filmId = stringToInt(parameters["film_id"]);
	if (purchasedFilmIds.find(filmId) != purchasedFilmIds.end())
		return;
	Film* film = filmRepository->getFilmById(filmId);
	int price = film->getPrice();

	if (money - price < 0)
		throw PermissionDeniedError();
	film->sell();
	money -= price;
	filmRepository->addWeightToEdgesBetween(filmId, purchasedFilmIds);
	purchasedFilmIds.insert(filmId);

	User* publisher = userRepository->getUserById(film->getPublisherId());
	publisher->getNotificationsRepository()->addNotification(new BuyYourFilmNotification(data["username"], id, film->getName(), filmId));
}

void User::follow(Map &parameters) {
    checkMustHave({"user_id"}, parameters);
	checkMayHave({"user_id"}, parameters);
	User* publisher = userRepository->getUserById(stringToInt(parameters["user_id"]));
    if (publisher->addFollower(id))
		publisher->getNotificationsRepository()->addNotification(new FollowYouNotification(data["username"], id));
}

void User::findFilms(Map &parameters) {
    set<int> filteredFilmsId = filmRepository->filterAllFilms(parameters);
    filmRepository->outputFilmsById(filteredFilmsId);
}

void User::rateFilm(Map &parameters) {
	int filmId = getAndCheckFilmId(parameters);
	Film* film = filmRepository->getFilmById(filmId);
	film->newRate(parameters, id);
	
	User* publisher = userRepository->getUserById(film->getPublisherId());
	publisher->getNotificationsRepository()->addNotification(new RateYourFilmNotification(data["username"], id, film->getName(), filmId));
}

void User::postComment(Map &parameters) {
	int filmId = getAndCheckFilmId(parameters);
    Film* film = filmRepository->getFilmById(filmId);
    film->addComment(parameters, id);

	User* publisher = userRepository->getUserById(film->getPublisherId());
	publisher->getNotificationsRepository()->addNotification(new CommentOnYourFilmNotification(data["username"], id, film->getName(), filmId));
}

void User::showFilm(Map &parameters) {
	int filmId = stringToInt(parameters["film_id"]);
	Film* film = filmRepository->getFilmById(filmId);
	film->outputDetails(parameters);
	set<int> excludedFilmIds = purchasedFilmIds;
	excludedFilmIds.insert(filmId);
	filmRepository->outputRecommendedFilmsFor(filmId, excludedFilmIds);
}

void User::outputPurchasedFilms(Map &parameters) {
	checkMayHave({"name", "price", "min_year", "max_year", "director"}, parameters);
    if (parameters.find("price") != parameters.end())
        checkNumeric(parameters["price"]);
    if (parameters.find("max_year") != parameters.end())
        checkNumeric(parameters["max_year"]);
    if (parameters.find("min_year") != parameters.end())
        checkNumeric(parameters["min_year"]);

    set<int> filteredFilmsId = filmRepository->filterFilms(parameters, purchasedFilmIds);
    filmRepository->outputFilmsById(filteredFilmsId);
}

int User::getAndCheckFilmId(Map &parameters) {
	int filmId = stringToInt(parameters["film_id"]);
	if (purchasedFilmIds.find(filmId) == purchasedFilmIds.end())
		throw PermissionDeniedError();
	return filmId;
}

void User::seeUnreadNotifications() {
	notificationsRepository->outputAllUnreadNotifications();
}

void User::seeReadNotifications(Map &parameters) {
	notificationsRepository->outputLastReadNotifications(parameters);
}

void User::makeAllNotificationsRead() {
	notificationsRepository->readAllNotifications();
}

void User::outputMoney() {
	print(vector<string> (1, intToString(money)));
}

NotificationsRepository* User::getNotificationsRepository() {
	return notificationsRepository;
}
string User::getUsername() {
    return data["username"];
}
string User::getPassword() {
    return data["password"];
}
string User::getEmail() {
    return data["email"];
}

bool User::addFollower(int id) {
    throw PermissionDeniedError();
}
void User::postFilm(Map &parameters) {
    throw PermissionDeniedError();
}
void User::editFilm(Map &parameters) {
    throw PermissionDeniedError();
}
void User::deleteFilm(Map &parameters) {
    throw PermissionDeniedError();
}
void User::outputFollowers(Map &parameters) {
    throw PermissionDeniedError();
}
void User::outputPublishedFilms(Map &parameters) {
    throw PermissionDeniedError();
}
void User::replyComment(Map &parameters) {
	throw PermissionDeniedError();
}
void User::deleteComment(Map &parameters) {
	throw PermissionDeniedError();
}
void User::collectEarning() {
	throw PermissionDeniedError();
}
