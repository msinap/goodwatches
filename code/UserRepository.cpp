#include "UserRepository.h"
#include "CommandManager.h"

UserRepository::UserRepository(CommandManager* _commandManager, FilmRepository* _filmRepository)
    : commandManager(_commandManager), filmRepository(_filmRepository) {
    users.push_back(NULL);
}

void UserRepository::addUser(Map &parameters) {
    if (parameters.find("publisher") == parameters.end() || parameters["publisher"] == "false") {
        users.push_back(new User(parameters, users.size(), this));
    } else if (parameters["publisher"] == "true") {
        users.push_back(new Publisher(parameters, users.size(), this));
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

void UserRepository::postFilm(Map &parameters) {
    if (loggedinUser == NULL)
        throw BadRequestError();
    if (loggedinUser->getType() == UserType::Normal)
        throw PermissionDeniedError();
    Publisher* loggedinPublisher = dynamic_cast<Publisher*> (loggedinUser);
    filmRepository->addFilm(parameters, loggedinPublisher);
}

User* UserRepository::findUserWithUsername(string username) {
    for (int id = 1; id < users.size(); id ++)
        if (users[id]->getUsername() == username)
            return users[id];
    return NULL;
}
