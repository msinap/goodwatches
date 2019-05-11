#ifndef USER_H
#define USER_H

#include "utility.h"

class User {
public:
    User(string _email, string _username, string _password, string _age, int _id);
    string getUsername();
    string getPassword();
protected:
    string email;
    string username;
    string password;
    string age;
    int id;
};

#endif
