#include "UserRepository.h"
#include "CommandManager.h"

UserRepository* UserRepository::userRepository = NULL;

UserRepository::UserRepository(FilmRepository* _filmRepository)
    : filmRepository(_filmRepository) {
	if (userRepository != NULL)
		return;
	userRepository = this;
    users.push_back(NULL);
	users.push_back(new Admin(_filmRepository));
	loggedInUserIds.insert(0);
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
	loggedInUserIds.insert(currentUser->getId());
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
	loggedInUserIds.insert(currentUser->getId());
}

void UserRepository::logoutCurrentUser() {
	if (currentUser == NULL)
		throw BadRequestError();
	currentUser->makeAllNotificationsRead();
	loggedInUserIds.erase(currentUser->getId());
	currentUser = NULL;
}

void UserRepository::changeCurrentUserTo(int id) {
	if (loggedInUserIds.find(id) == loggedInUserIds.end())
		throw BadRequestError();
	if (id == 0) {
		currentUser = NULL; 
	}else if (id == 1) {
		currentUser = getAdmin();
	}else {
		currentUser = getUserById(id);
	}
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

int UserRepository::getCurrentUserId() {
	if (currentUser == NULL)
		return 0;
	return currentUser->getId();
}