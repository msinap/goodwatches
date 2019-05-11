#include "UserRepository.h"
#include "CommandManager.h"

const vector<string> UserRepository::validKeysForSignup = {"email", "username", "password", "age", "publisher"};
const vector<bool> UserRepository::shouldExistKeysForSignup = {true, true, true, true, false};

UserRepository::UserRepository(CommandManager* _commandManager)
    : commandManager(_commandManager) {
}

void UserRepository::addUser(vector<string> &remainingWordsOfLine) {
    map<string, string> map = commandManager->setValuesInKeys(remainingWordsOfLine, validKeysForSignup,
                                                              shouldExistKeysForSignup);
    if(findUserWithUsername(map["username"]) != NULL)
        throw BadRequestError();

    if (map.find("publisher") == map.end() || map["publisher"] == "false") {
        users.push_back(new User(map["email"], map["username"], map["password"], map["age"], users.size()+1));
    }else if(map["publisher"] == "true"){
        users.push_back(new Publisher(map["email"], map["username"], map["password"], map["age"], users.size()+1));
    }else {
        throw BadRequestError();
    }
}

User* UserRepository::findUserWithUsername(string username) {
    for (User* user : users)
        if (user->getUsername() == username)
            return user;
    return NULL;
}
