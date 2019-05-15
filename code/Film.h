#ifndef FILM_H
#define FILM_H

#include "utility.h"
#include "CommentRepository.h"

class Film {
public:
    Film(Map &parameters, int _id);
    void edit(Map &parameters);
    void stopSale(Map &parameters);
	void addComment(Map &parameters);
	void replyComment(Map &parameters);
	void deleteComment(Map &parameters);
	void outputDetails(Map &parameters);
	bool areFiltersPassed(Map &parameters);
	void newRate(Map &parameters, int userId);
	vector<string> getOutput(bool allDetails = true);
	int getPriceAndSell();
	double getRate();
	bool isForSale();
	int getEarning();
private:
    Map data;
    bool forSale;
	map<int, int> userRates;
	int sumOfRates;
	int uncollectedEarning;
    CommentRepository* commentRepository;
};

#endif
