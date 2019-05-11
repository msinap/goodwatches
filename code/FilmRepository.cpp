#include "FilmRepository.h"

FilmRepository::FilmRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
}

void FilmRepository::addFilm(vector<string> &remainingWordsOfLine, Publisher* _owner) {
    films.push_back(new Film(remainingWordsOfLine, _owner, commandManager));
}
