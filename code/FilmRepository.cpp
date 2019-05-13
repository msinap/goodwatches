#include "FilmRepository.h"

FilmRepository::FilmRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
    films.push_back(NULL);
}

set<int> FilmRepository::filterFilms(Map &parameters, set<int> &filmsId) {
    set<int> filteredFilmsId;
    for (int filmId : filmsId) {
        Film* film = getFilmWithId(filmId);
        Map filmData = film->getData();
        bool passFilter = true;
        for (auto &x : parameters) {
            string key = x.first, value = x.second;
            if (key == "name" || key == "price" || key == "director") {
                if (filmData[key] != value)
                    passFilter = false;
            }else if (key == "min_year") {
                if (filmData["year"] < addLeadingZeros(value))
                    passFilter = false;
            }else if (key == "max_year") {
                if (filmData["year"] > addLeadingZeros(value))
                    passFilter = false;
            }else if (key == "min_rate") {
                //TODO
            }
        }
        if (passFilter)
            filteredFilmsId.insert(filmId);
    }
    return filteredFilmsId;
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
