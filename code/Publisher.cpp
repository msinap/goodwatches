#include "Publisher.h"
#include "UserRepository.h"
#include "FilmRepository.h"

Publisher::Publisher(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : User(parameters, id, ur, fr) {
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
	if (parameters.find("min_rate") != parameters.end())
        checkNumeric(parameters["min_rate"]);

    set<int> filteredFilmsId = filmRepository->filterFilms(parameters, publishedFilmIds);
    filmRepository->outputFilmsById(filteredFilmsId);
}

void Publisher::collectEarning() {
	for (int filmId : publishedFilmIds) {
		Film* film = filmRepository->getFilmWithId(filmId);
		money += film->getEarning();
	}
}

void Publisher::deleteComment(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
	filmRepository->getFilmWithId(id)->deleteComment(parameters);
}

void Publisher::replyComment(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
	filmRepository->getFilmWithId(id)->replyComment(parameters);
}

void Publisher::postFilm(Map &parameters) {
    filmRepository->addFilm(parameters);
    publishedFilmIds.insert(filmRepository->getLastId());
}

void Publisher::editFilm(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
    filmRepository->getFilmWithId(id)->edit(parameters);
}

void Publisher::deleteFilm(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
    filmRepository->getFilmWithId(id)->stopSale(parameters);
}

int Publisher::getAndCheckFilmId(Map &parameters) {
    int id = stringToInt(parameters["film_id"]);
    if (publishedFilmIds.find(id) == publishedFilmIds.end())
        throw PermissionDeniedError();
    return id;
}
