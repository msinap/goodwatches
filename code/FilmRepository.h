#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include "utility.h"
#include "Film.h"

class CommandManager;
class Publisher;

class FilmRepository {
public:
    FilmRepository(CommandManager* _commandManager);
    void addFilm(Map &parameters);
    set<int> filterFilms(Map &parameters, set<int> &filmsId);
    set<int> filterAllFilms(Map &parameters);
    void printAndMakeOutput(set<int> filmsId);
    Film* getFilmWithId(int id);
    int getLastId();
private:
    vector<Film*> films;
    CommandManager* commandManager;
};

#endif
