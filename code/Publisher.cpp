#include "Publisher.h"
#include "UserRepository.h"
#include "FilmRepository.h"

Publisher::Publisher(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : User(parameters, id, ur, fr) {
}

UserType Publisher::getType() {
    return UserType::Publisher;
}

void Publisher::addFollower(int id) {
    followers.insert(id);
}

void Publisher::outputFollowers(Map &parameters) {
    checkMayHave({}, parameters);
    set<vector<string>> output;
    for (int userId : followers) {
        User* user = userRepository->getUserWithId(userId);
        vector<string> userOutput;
        userOutput.push_back(intToString(userId));
        userOutput.push_back(user->getUsername());
        userOutput.push_back(user->getEmail());
        output.insert(userOutput);
    }
    print({"User Id", "User Username", "User Email"}, output, "List of Followers");
}

void Publisher::outputPublishedFilms(Map &parameters) {
    checkMayHave({"name", "min_rate", "price", "min_year", "max_year", "director"}, parameters);
    if (parameters.find("price") != parameters.end())
        checkNumeric(parameters["price"]);
    if (parameters.find("max_year") != parameters.end())
        checkNumeric(parameters["max_year"]);
    if (parameters.find("min_year") != parameters.end())
        checkNumeric(parameters["min_year"]);

    set<int> filteredFilmsId = filmRepository->filterFilms(parameters, filmsId);
    set<vector<string>> output = filmRepository->makeOutput(filteredFilmsId);
    print({"Film Id", "Film Name", "Film Length", "Film Price", "Rate", "Production Year", "Film Director"},
          output, "");
}

void Publisher::postFilm(Map &parameters) {
    filmRepository->addFilm(parameters);
    filmsId.insert(filmRepository->getLastId());
}

void Publisher::editFilm(Map &parameters) {
    filmRepository->getFilmWithId(getAndCheckFilmIdFrom(parameters))->edit(parameters);
}

void Publisher::deleteFilm(Map &parameters) {
    filmRepository->getFilmWithId(getAndCheckFilmIdFrom(parameters))->stopSale(parameters);
}

int Publisher::getAndCheckFilmIdFrom(Map &parameters) {
    int id = stringToInt(parameters["film_id"]);
    if (filmsId.find(id) == filmsId.end())
        throw PermissionDeniedError();
    return id;
}
