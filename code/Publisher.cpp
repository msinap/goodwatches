#include "Publisher.h"
#include "UserRepository.h"
#include "FilmRepository.h"
#include "NotificationsRepository.h"
#include "Notifications.h"

Publisher::Publisher(Map &parameters, int id, UserRepository* ur, FilmRepository* fr)
    : User(parameters, id, ur, fr) {
}

bool Publisher::addFollower(int id) {
	bool ret = (followerIds.find(id) == followerIds.end());
	followerIds.insert(id);
	return ret;
}

void Publisher::outputFollowers(Map &parameters) {
    checkMayHave({}, parameters);
    set<vector<string>> output;
    for (int followerId : followerIds) {
        User* follower = userRepository->getUserById(followerId);
        vector<string> followerOutput;
        followerOutput.push_back(intToString(followerId));
        followerOutput.push_back(follower->getUsername());
        followerOutput.push_back(follower->getEmail());
        output.insert(followerOutput);
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
		Film* film = filmRepository->getFilmById(filmId);
		money += film->collectEarning();
	}
}

void Publisher::deleteComment(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
	filmRepository->getFilmById(id)->deleteComment(parameters);
}

void Publisher::replyComment(Map &parameters) {
	int filmId = getAndCheckFilmId(parameters);
	Film* film = filmRepository->getFilmById(filmId);
	film->replyComment(parameters);
	int senderId = film->getSenderOfCommentId(stringToInt(parameters["comment_id"]));
	User* sender = userRepository->getUserById(senderId);
	sender->getNotificationsRepository()->addNotification(new ReplyToYourCommentNotification(data["username"], id));
}

void Publisher::postFilm(Map &parameters) {
    filmRepository->addFilm(parameters, id);
    publishedFilmIds.insert(filmRepository->getLastId());
	for (int followerId : followerIds) {
		User* follower = userRepository->getUserById(followerId);
		follower->getNotificationsRepository()->addNotification(new RegisterNewFilmNotification(data["username"], id));
	}
}

void Publisher::editFilm(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
    filmRepository->getFilmById(id)->edit(parameters);
}

void Publisher::deleteFilm(Map &parameters) {
	int id = getAndCheckFilmId(parameters);
    filmRepository->getFilmById(id)->stopSale(parameters);
}

int Publisher::getAndCheckFilmId(Map &parameters) {
    int id = stringToInt(parameters["film_id"]);
    if (publishedFilmIds.find(id) == publishedFilmIds.end())
        throw PermissionDeniedError();
    return id;
}
