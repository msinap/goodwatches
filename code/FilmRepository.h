#ifndef FILMREPOSITORY_H
#define FILMREPOSITORY_H

#include "utility.h"
#include "Film.h"

class Publisher;

class FilmRepository {
public:
    FilmRepository();
    void addFilm(Map &parameters, int publisherId);
    set<int> filterFilms(Map &parameters, set<int> &filmsId);
    set<int> filterAllFilms(Map &parameters);
    void outputFilmsById(set<int> filmsId);
	void outputRecommendedFilmsFor(int filmId, set<int> excludedIds);
	void addWeightToEdgesBetween(int filmId, set<int> otherIds);
	int getSumOfAdminShares();
	int getSumOfUncollectedMoney();
    Film* getFilmById(int id);
    int getLastId();
private:
    vector<Film*> films;
	map<pair<int, int>, int> adjacencyMatrix;
};

#endif
