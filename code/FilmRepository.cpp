#include "FilmRepository.h"

FilmRepository::FilmRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
    films.push_back(NULL);
}

set<int> FilmRepository::filterFilms(Map &parameters, set<int> &filmsId) {
    set<int> filteredFilmsId;
    for (int filmId : filmsId) {
        Film* film = getFilmById(filmId);
        if (film->areFiltersPassed(parameters))
            filteredFilmsId.insert(filmId);
    }
    return filteredFilmsId;
}

set<int> FilmRepository::filterAllFilms(Map &parameters) {
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

void FilmRepository::outputBestFilms(set<int> excludedIds) {
	set<pair<double, double>> sortedFilms;
	for (int id = 1; id < films.size(); id++) {
		if (excludedIds.find(id) != excludedIds.end())
			continue;
		Film* film = getFilmById(id);
		if (!film->isForSale())
			continue;
		sortedFilms.insert({10.0 - film->getRate(), id});
	}
	
	vector<vector<string>> output; 
	for (pair<double, double> sortMaterial : sortedFilms) {
		int id = sortMaterial.second;
		Film* film = getFilmById(id);
		output.push_back(film->getOutput(false));
	}
	print({"Film Id", "Film Name", "Film Length", "Film Director"}, output, "\nRecommendation Film");
}

int FilmRepository::getLastId() {
    return films.size() - 1;
}

Film* FilmRepository::getFilmById(int id) {
    if (id == 0 || id >= films.size())
        throw PermissionDeniedError();
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