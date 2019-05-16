#include "User.h"
#include "UserRepository.h"
#include "FilmRepository.h"

User::User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : data(parameters), id(_id), userRepository(ur), filmRepository(fr), money(0) {
    checkMustHave({"email", "username", "password", "age"}, data);
    checkMayHave ({"email", "username", "password", "age", "publisher"}, data);
    checkEmail(parameters["email"]);
    if(userRepository->findUserWithUsername(data["username"]) != NULL)
        throw BadRequestError();
    checkNumeric(parameters["age"]);
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
	int price = filmRepository->getFilmById(filmId)->getPriceAndSell();
	if (money - price < 0)
		throw BadRequestError();
	money -= price;
	purchasedFilmIds.insert(filmId);
}

void User::follow(Map &parameters) {
    checkMustHave({"user_id"}, parameters);
    userRepository->getUserWithId(stringToInt(parameters["user_id"]))->addFollower(id);
}

void User::findFilms(Map &parameters) {
    set<int> filteredFilmsId = filmRepository->filterAllFilms(parameters);
    filmRepository->outputFilmsById(filteredFilmsId);
}

void User::rateFilm(Map &parameters) {
	int filmId = getAndCheckFilmId(parameters);
	filmRepository->getFilmById(filmId)->newRate(parameters, id);
}

void User::postComment(Map &parameters) {
	int filmId = getAndCheckFilmId(parameters);
    Film* film = filmRepository->getFilmById(filmId);
    film->addComment(parameters);
}

void User::showFilm(Map &parameters) {
	int filmId = stringToInt(parameters["film_id"]);
	Film* film = filmRepository->getFilmById(filmId);
	film->outputDetails(parameters);
	filmRepository->outputBestFilms(purchasedFilmIds);
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

string User::getUsername() {
    return data["username"];
}
string User::getPassword() {
    return data["password"];
}
string User::getEmail() {
    return data["email"];
}

void User::addFollower(int id) {
    throw BadRequestError();
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
