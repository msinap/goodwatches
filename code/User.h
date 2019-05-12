#ifndef USER_H
#define USER_H

#include "utility.h"

enum class UserType {Normal, Publisher};

class UserRepository;

class User {
public:
    User(Map &parameters, int _id, UserRepository* r);
    string getUsername();
    string getPassword();
    virtual UserType getType();
protected:
    Map data;
    int id;
    UserRepository* userRepository;
};

#endif
