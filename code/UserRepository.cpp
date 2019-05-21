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
	changeLoggedinUserTo(users.back());
}

void UserRepository::login(Map &parameters) {
    checkMustHave({"username", "password"}, parameters);
    User* user = findUserWithUsername(parameters["username"]);
    if (user == NULL)
        throw BadRequestError();
    if (user->getPassword() != hashFletcherCRC(parameters["password"]))
        throw BadRequestError();
	changeLoggedinUserTo(user);
}

void UserRepository::logoutLoggedInUser() {
	if (loggedinUser == NULL)
		throw BadRequestError();
	loggedinUser->logout();
	loggedinUser = NULL;
}

void UserRepository::changeLoggedinUserTo(User* user) {
	if (loggedinUser != NULL)
		throw BadRequestError();
	loggedinUser = user;
}

User* UserRepository::getLoggedinUser() {
    if (loggedinUser == NULL)
        throw PermissionDeniedError();
    return loggedinUser;
}

User* UserRepository::getUserById(int id) {
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
