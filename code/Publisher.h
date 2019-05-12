#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "utility.h"
#include "User.h"

class UserRepository;

class Publisher : public User {
public:
    Publisher(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr);
    virtual UserType getType();
    virtual void postFilm(Map &parameters);
protected:

};

#endif