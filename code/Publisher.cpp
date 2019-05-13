#include "Publisher.h"
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
