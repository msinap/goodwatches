#include "UserRepository.h"
#include "CommandManager.h"

UserRepository* UserRepository::userRepository = NULL;

UserRepository::UserRepository(FilmRepository* _filmRepository)
    : filmRepository(_filmRepository), currentUserId(0) {
	if (userRepository != NULL)
		return;
	userRepository = this;
    users.push_back(NULL);
	users.push_back(new Admin(_filmRepository));
}

void UserRepository::addUser(Map &parameters) {
	if (currentUser != NULL)
		throw BadRequestError();
    if (parameters.find("publisher") == parameters.end() || parameters["publisher"] == "false") {
        users.push_back(new User(parameters, users.size(), this, filmRepository));
    } else if (parameters["publisher"] == "true") {
        users.push_back(new Publisher(parameters, users.size(), this, filmRepository));
    } else {
        throw BadRequestError();
    }
	currentUser = users.back();
}

void UserRepository::login(Map &parameters) {
	if (currentUser != NULL)
		throw BadRequestError();
    checkMustHave({"username", "password"}, parameters);
    User* user = findUserWithUsername(parameters["username"]);
    if (user == NULL)
        throw BadRequestError();
    if (user->getPassword() != hashFletcherCRC(parameters["password"]))
        throw BadRequestError();
	currentUser = user;
}

void UserRepository::logoutCurrentUser() {
	if (currentUser == NULL)
		throw BadRequestError();
	currentUser->makeAllNotificationsRead();
	currentUser = NULL;
}

void UserRepository::changeCurrentUserTo(int id) {
	if (id == 0) {
		currentUser = NULL; 
	}else if (id == 1) {
		currentUser = getAdmin();
	}else {
		currentUser = getUserById(id);
	}
	currentUserId = id;
}

User* UserRepository::getCurrentUser() {
    if (currentUser == NULL)
        throw PermissionDeniedError();
    return currentUser;
}

User* UserRepository::getUserById(int id) {
    if (id <= 0 || id >= users.size())
        throw NotFoundError();
	if (id == 1)
		throw PermissionDeniedError();
    return users[id];
}

User* UserRepository::findUserWithUsername(string username) {
    for (int id = 1; id < users.size(); id ++)
        if (users[id]->getUsername() == username)
            return users[id];
    return NULL;
}

Admin* UserRepository::getAdmin() {
	return dynamic_cast<Admin*>(users[1]);
}
