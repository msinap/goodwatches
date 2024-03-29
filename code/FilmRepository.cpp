#include "FilmRepository.h"

FilmRepository* FilmRepository::filmRepository = NULL;

FilmRepository::FilmRepository() {
	if (filmRepository != NULL)
		return;
	filmRepository = this;
    films.push_back(NULL);
}

set<int> FilmRepository::filterFilms(Map &parameters, set<int> &filmsId) {
	if (parameters["director"] == "")
		parameters.erase("director");
	checkMayHave({"name", "min_year", "max_year", "min_rate", "price", "director"}, parameters);
    if (parameters.find("price") != parameters.end())
        checkNumeric(parameters["price"]);
    if (parameters.find("max_year") != parameters.end())
        checkNumeric(parameters["max_year"]);
    if (parameters.find("min_year") != parameters.end())
        checkNumeric(parameters["min_year"]);
	if (parameters.find("min_rate") != parameters.end())
        checkNumeric(parameters["min_rate"]);

    set<int> filteredFilmsId;
    for (int filmId : filmsId) {
        Film* film = getFilmById(filmId);
        if (film->areFiltersPassed(parameters))
            filteredFilmsId.insert(filmId);
    }
    return filteredFilmsId;
}

set<int> FilmRepository::filterAllFilms(Map &parameters) {
	if (parameters["director"] == "")
		parameters.erase("director");
	checkMayHave({"name", "min_year", "max_year", "min_rate", "price", "director"}, parameters);
    if (parameters.find("price") != parameters.end())
        checkNumeric(parameters["price"]);
    if (parameters.find("max_year") != parameters.end())
        checkNumeric(parameters["max_year"]);
    if (parameters.find("min_year") != parameters.end())
        checkNumeric(parameters["min_year"]);
	if (parameters.find("min_rate") != parameters.end())
        checkNumeric(parameters["min_rate"]);

    set<int> filteredFilmsId;
    for (int filmId = 1; filmId < films.size(); filmId ++) {
        Film* film = getFilmById(filmId);
        if (film->areFiltersPassed(parameters))
            filteredFilmsId.insert(filmId);
    }
    return filteredFilmsId;
}

void FilmRepository::outputFilmsById(set<int> filmsId) {
    set<vector<string>> output;
    for (int filmId : filmsId) {
        Film* film = getFilmById(filmId);
        vector<string> filmOutput = film->getOutput();
        output.insert(filmOutput);
    }
    print({"Film Id", "Film Name", "Film Length", "Film price", "Rate", "Production Year", "Film Director"},
		   output, "");
}

void FilmRepository::addWeightToEdgesBetween(int filmId, set<int> otherIds) {
	for (int otherId : otherIds) {
		adjacencyMatrix[{filmId, otherId}] ++;
		adjacencyMatrix[{otherId, filmId}] ++;
	}
}

vector<int> FilmRepository::getRecommendedFilmIdsFor(int filmId, set<int> excludedIds) {
	set<pair<double, double>> sortedFilms;
	vector<int> returnIds;
	for (int otherId = 1; otherId < films.size(); otherId++) {
		if (excludedIds.find(otherId) != excludedIds.end())
			continue;
		Film* film = getFilmById(otherId);
		if (!film->isForSale())
			continue;
		sortedFilms.insert({-adjacencyMatrix[{filmId, otherId}], otherId});
	}	
	vector<vector<string>> output;
	for (pair<double, double> sortMaterial : sortedFilms) {
		int id = sortMaterial.second;
		Film* film = getFilmById(id);
		returnIds.push_back(id);
		output.push_back(film->getOutput(false));
		if (output.size() == 4)
			break;
	}
	return returnIds;
	//print({"Film Id", "Film Name", "Film Length", "Film Director"}, output, "\nRecommendation Film");
}

int FilmRepository::getLastId() {
    return films.size() - 1;
}

Film* FilmRepository::getFilmById(int id) {
    if (id <= 0 || id >= films.size())
        throw NotFoundError();
    return films[id];
}

void FilmRepository::addFilm(Map &parameters, int publisherId) {
    films.push_back(new Film(parameters, films.size(), publisherId));
}

int FilmRepository::getSumOfAdminShares() {
	int sum = 0;
	for (int id = 1; id < films.size(); id ++)
		sum += films[id]->getAdminShare();
	return sum;
}

int FilmRepository::getSumOfUncollectedMoney() {
	int sum = 0;
	for (int id = 1; id < films.size(); id ++)
		sum += films[id]->getUncollectedMoney();
	return sum;
}