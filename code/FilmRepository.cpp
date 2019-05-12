#include "FilmRepository.h"

FilmRepository::FilmRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
    films.push_back(NULL);
}

int FilmRepository::getLastId() {
    return films.size() - 1;
}

Film* FilmRepository::getFilmWithId(int id) {
    if (id == 0 || id >= films.size())
        throw PermissionDeniedError();
    return films[id];
}

void FilmRepository::addFilm(Map &parameters) {
    films.push_back(new Film(parameters));
}
