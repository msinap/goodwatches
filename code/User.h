#ifndef USER_H
#define USER_H

#include "utility.h"

enum class UserType {Normal, Publisher};

class UserRepository;
class FilmRepository;

class User {
public:
    User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr);
    string getUsername();
    string getPassword();
    virtual UserType getType();
    virtual void postFilm(Map &parameters);
    virtual void editFilm(Map &parameters);
    virtual void deleteFilm(Map &parameters);
protected:
    Map data;
    int id;
    UserRepository* userRepository;
    FilmRepository* filmRepository;
};

#endif
