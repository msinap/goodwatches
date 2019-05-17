#ifndef FILM_H
#define FILM_H

#include "utility.h"
#include "CommentRepository.h"

class Film {
public:
    Film(Map &parameters, int _id, int _publisherId);
    void edit(Map &parameters);
    void stopSale(Map &parameters);
	void replyComment(Map &parameters);
	void deleteComment(Map &parameters);
	void outputDetails(Map &parameters);
	bool areFiltersPassed(Map &parameters);
	void newRate(Map &parameters, int userId);
	void addComment(Map &parameters, int senderId);
	vector<string> getOutput(bool allDetails = true);
	int getSenderOfCommentId(int commentId);
	int getPriceAndSell();
	int getPublisherId();
	double getRate();
	bool isForSale();
	int getEarning();
	string getName();
private:
    Map data;
    bool forSale;
	int publisherId;
	map<int, int> userRates;
	int sumOfRates;
	int uncollectedEarning;
    CommentRepository* commentRepository;
};

#endif
