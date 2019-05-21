#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include "utility.h"
#include "Film.h"

class CommandManager;
class Publisher;

class FilmRepository {
public:
    FilmRepository(CommandManager* _commandManager);
    void addFilm(Map &parameters, int publisherId);
    set<int> filterFilms(Map &parameters, set<int> &filmsId);
    set<int> filterAllFilms(Map &parameters);
    void outputFilmsById(set<int> filmsId);
	void outputBestFilms(set<int> excludedIds);
	int getSumOfAdminShares();
    Film* getFilmById(int id);
    int getLastId();
private:
    vector<Film*> films;
    CommandManager* commandManager;
};

#endif
