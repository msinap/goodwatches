#ifndef FILM_H
#define FILM_H

#include "utility.h"
#include "CommentRepository.h"

class Film {
public:
    Film(Map &parameters, int _id);
    void edit(Map &parameters);
    void stopSale(Map &parameters);
    vector<string> getOutput();
    bool areFiltersPassed(Map &parameters);
    bool isForSale();
private:
    Map data;
    int id;
    bool forSale;
    CommentRepository* commentRepository;
};

#endif
