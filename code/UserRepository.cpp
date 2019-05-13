#include "UserRepository.h"
#include "CommandManager.h"

UserRepository::UserRepository(CommandManager* _commandManager, FilmRepository* _filmRepository)
    : commandManager(_commandManager), filmRepository(_filmRepository) {
    users.push_back(NULL);
}

void UserRepository::addUser(Map &parameters) {
    if (parameters.find("publisher") == parameters.end() || parameters["publisher"] == "false") {
        users.push_back(new User(parameters, users.size(), this, filmRepository));
    } else if (parameters["publisher"] == "true") {
        users.push_back(new Publisher(parameters, users.size(), this, filmRepository));
    } else {
        throw BadRequestError();
    }
    loggedinUser = users.back();
}

void UserRepository::login(Map &parameters) {
    checkMustHave({"username", "password"}, parameters);
    User* user = findUserWithUsername(parameters["username"]);
    if (user == NULL)
        throw PermissionDeniedError();
    if (user->getPassword() != parameters["password"])
        throw BadRequestError();
    loggedinUser = user;
}

User* UserRepository::getLoggedinUser() {
    if (loggedinUser == NULL)
        throw PermissionDeniedError();
    return loggedinUser;
}

User* UserRepository::getUserWithId(int id) {
    if (id < 1 || id >= users.size())
        throw BadRequestError();
    return users[id];
}

User* UserRepository::findUserWithUsername(string username) {
    for (int id = 1; id < users.size(); id ++)
        if (users[id]->getUsername() == username)
            return users[id];
    return NULL;
}
