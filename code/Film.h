#ifndef FILM_H
#define FILM_H

#include "utility.h"
#include "CommentRepository.h"

class Film {
public:
    Film(Map &parameters, int _id, int _publisherId);
	void sell();
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
	int getUncollectedMoney();
	int getPublisherId();
	int collectEarning();
	int getAdminShare();
	double getRate();
	bool isForSale();
	string getName();
	int getPrice();
	Map getData();
private:
    Map data;
    bool forSale;
	int publisherId;
	map<int, int> userRates;
	int sumOfRates;
	int uncollectedEarning;
	int adminShare;
    CommentRepository* commentRepository;
};

#endif
