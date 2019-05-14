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
	void outputDetails(Map &parameters);
	bool areFiltersPassed(Map &parameters);
	bool isForSale();
	vector<string> getOutput();
private:
    Map data;
    bool forSale;
    CommentRepository* commentRepository;
};

#endif
