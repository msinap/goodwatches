#ifndef USERREPOSITORY
#define USERREPOSITORY

#include "utility.h"
#include "User.h"
#include "Publisher.h"

class UserRepository {
public:
    void addUser(vector<string> &remainingWordsOfLine);
private:
    vector<User*> users;
};

#endif
