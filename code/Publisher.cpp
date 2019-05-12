#include "Publisher.h"
#include "FilmRepository.h"

Publisher::Publisher(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : User(parameters, id, ur, fr) {
}

UserType Publisher::getType() {
    return UserType::Publisher;
}

void Publisher::postFilm(Map &parameters) {
    filmRepository->addFilm(parameters, this);
}
