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
    void follow(Map &parameters);
    virtual void postFilm(Map &parameters);
    virtual void editFilm(Map &parameters);
    virtual void deleteFilm(Map &parameters);
    virtual void addFollower(int id);
    virtual UserType getType();
protected:
    Map data;
    int id;
    UserRepository* userRepository;
    FilmRepository* filmRepository;
};

#endif
