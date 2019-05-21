#ifndef USERREPOSITORY
#define USERREPOSITORY

#include "utility.h"
#include "User.h"
#include "Publisher.h"
#include "FilmRepository.h"

class CommandManager;

class UserRepository {
public:
    UserRepository(CommandManager* _commandManager, FilmRepository* _filmRepository);
    void addUser(Map &parameters);
    void login(Map &parameters);
	void logoutLoggedInUser();
    User* getLoggedinUser();
    User* findUserWithUsername(string username);
    User* getUserById(int id);
private:
	void changeLoggedinUserTo(User* user);

    CommandManager* commandManager;
    FilmRepository* filmRepository;
    vector<User*> users;
    User* loggedinUser;
};

#endif
