#ifndef USERREPOSITORY
#define USERREPOSITORY

#include "utility.h"
#include "User.h"
#include "Publisher.h"

class CommandManager;

class UserRepository {
public:
    UserRepository(CommandManager* _commandManager);
    void addUser(vector<string> &remainingWordsOfLine);
private:
    User* findUserWithUsername(string username);

    CommandManager* commandManager;
    vector<User*> users;

    const static vector<string> validKeysForSignup;
    const static vector<bool> shouldExistKeysForSignup;
};

#endif
