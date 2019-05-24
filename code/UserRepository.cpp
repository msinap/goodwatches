#include "UserRepository.h"
#include "CommandManager.h"

UserRepository::UserRepository(CommandManager* _commandManager, FilmRepository* _filmRepository)
    : commandManager(_commandManager), filmRepository(_filmRepository), admin(new Admin(_filmRepository)) {
    users.push_back(NULL);
}

void UserRepository::addUser(Map &parameters) {
	if (loggedinUser != NULL)
		throw PermissionDeniedError();
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
	if (loggedinUser != NULL)
		throw PermissionDeniedError();
    checkMustHave({"username", "password"}, parameters);
    User* user = findUserWithUsername(parameters["username"]);
    if (user == NULL)
        throw BadRequestError();
    if (user->getPassword() != hashFletcherCRC(parameters["password"]))
        throw BadRequestError();
	loggedinUser = user;
}

void UserRepository::logoutLoggedInUser() {
	if (loggedinUser == NULL)
		throw BadRequestError();
	loggedinUser->makeAllNotificationsRead();
	loggedinUser = NULL;
}

User* UserRepository::getLoggedinUser() {
    if (loggedinUser == NULL)
        throw PermissionDeniedError();
    return loggedinUser;
}

User* UserRepository::getUserById(int id) {
    if (id <= 0 || id >= users.size())
        throw NotFoundError();
    return users[id];
}

User* UserRepository::findUserWithUsername(string username) {
	if (username == "admin")
		return admin;
    for (int id = 1; id < users.size(); id ++)
        if (users[id]->getUsername() == username)
            return users[id];
    return NULL;
}

Admin* UserRepository::getAdmin() {
	return admin;
}
