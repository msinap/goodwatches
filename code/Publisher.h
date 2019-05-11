#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "utility.h"
#include "User.h"

class Publisher : public User {
public:
    Publisher(string _email, string _username, string _password, string _age, int _id);
    virtual UserType getType();
protected:

};

#endif
