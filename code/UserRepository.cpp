#include "UserRepository.h"
#include "CommandManager.h"

const vector<string> UserRepository::validKeysForSignup = {"email", "username", "password", "age", "publisher"};
const vector<bool> UserRepository::shouldExistKeysForSignup = {true, true, true, true, false};
const vector<string> UserRepository::validKeysForLogin = {"username", "password"};
const vector<bool> UserRepository::shouldExistKeysForLogin = {true, true};

UserRepository::UserRepository(CommandManager* _commandManager, FilmRepository* _filmRepository)
    : commandManager(_commandManager), filmRepository(_filmRepository) {
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

void UserRepository::login(vector<string> &remainingWordsOfLine) {
    map<string, string> map = commandManager->setValuesInKeys(remainingWordsOfLine, validKeysForLogin,
                                                              shouldExistKeysForLogin);
    User* user = findUserWithUsername(map["username"]);
    if (user == NULL)
        throw BadRequestError();
    if (user->getPassword() != map["password"])
        throw BadRequestError();
    loggedinUser = user;
}

void UserRepository::postFilm(vector<string> &remainingWordsOfLine) {
    if (loggedinUser == NULL)
        throw BadRequestError();
    if (loggedinUser->getType() == UserType::Normal)
        throw PermissionDeniedError();
    Publisher* loggedinPublisher = dynamic_cast<Publisher*> (loggedinUser);
    filmRepository->addFilm(remainingWordsOfLine, loggedinPublisher);
}

User* UserRepository::findUserWithUsername(string username) {
    for (User* user : users)
        if (user->getUsername() == username)
            return user;
    return NULL;
}
