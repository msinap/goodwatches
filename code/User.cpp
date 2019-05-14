#include "User.h"
#include "UserRepository.h"
#include "FilmRepository.h"

User::User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : data(parameters), id(_id), userRepository(ur), filmRepository(fr) {
    checkMustHave({"email", "username", "password", "age"}, data);
    checkMayHave ({"email", "username", "password", "age", "publisher"}, data);
    //TODO checkEmail(parameters["email"]);
    if(userRepository->findUserWithUsername(data["username"]) != NULL)
        throw BadRequestError();
    checkNumeric(parameters["age"]);
}

void User::follow(Map &parameters) {
    checkMustHave({"user_id"}, parameters);
    userRepository->getUserWithId(stringToInt(parameters["user_id"]))->addFollower(id);
}

void User::findFilms(Map &parameters) {
    checkMayHave({"name", "min_year", "max_year", "min_rate", "price", "director"}, parameters);
    if (parameters.find("price") != parameters.end())
        checkNumeric(parameters["price"]);
    if (parameters.find("max_year") != parameters.end())
        checkNumeric(parameters["max_year"]);
    if (parameters.find("min_year") != parameters.end())
        checkNumeric(parameters["min_year"]);

    set<int> filteredFilmsId = filmRepository->filterAllFilms(parameters);
    filmRepository->outputFilmsById(filteredFilmsId);
}

void User::postComment(Map &parameters) {
    Film* film = filmRepository->getFilmWithId(stringToInt(parameters["film_id"]));
    film->addComment(parameters);
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
UserType User::getType() {
    return UserType::Normal;
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
