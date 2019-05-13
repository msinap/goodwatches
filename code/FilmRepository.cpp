#include "FilmRepository.h"

FilmRepository::FilmRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
    films.push_back(NULL);
}

set<int> FilmRepository::filterFilms(Map &parameters, set<int> &filmsId) {
    set<int> filteredFilmsId;
    for (int filmId : filmsId) {
        Film* film = getFilmWithId(filmId);
        if (film->areFiltersPassed(parameters))
            filteredFilmsId.insert(filmId);
    }
    return filteredFilmsId;
}

set<vector<string>> FilmRepository::makeOutput(set<int> filmsId) {
    set<vector<string>> output;
    for (int filmId : filmsId) {
        Film* film = getFilmWithId(filmId);
        vector<string> filmOutput = film->getOutput();
        output.insert(filmOutput);
    }
    return output;
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
    films.push_back(new Film(parameters, films.size()));
}
