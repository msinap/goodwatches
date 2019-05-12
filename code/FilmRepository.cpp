#include "FilmRepository.h"

FilmRepository::FilmRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
    films.push_back(NULL);
}

void FilmRepository::addFilm(Map &parameters, Publisher* _owner) {
    films.push_back(new Film(parameters, _owner, films.size()));
}
