#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include "utility.h"
#include "Film.h"

class CommandManager;
class Publisher;

class FilmRepository {
public:
    FilmRepository(CommandManager* _commandManager);
    void addFilm(Map &parameters, Publisher* _owner);
private:
    vector<Film*> films;
    CommandManager* commandManager;
};

#endif
