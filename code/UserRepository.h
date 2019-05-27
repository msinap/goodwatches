#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "utility.h"
#include "User.h"
#include "Publisher.h"
#include "Admin.h"
#include "FilmRepository.h"

class UserRepository {
public:
    UserRepository(FilmRepository* _filmRepository);
	static UserRepository* userRepository;
    void addUser(Map &parameters);
    void login(Map &parameters);
	void logoutCurrentUser();
	void changeCurrentUserTo(int id);
    User* getCurrentUser();
	int getCurrentUserId();
    User* findUserWithUsername(string username);
    User* getUserById(int id);
	Admin* getAdmin();
private:
    FilmRepository* filmRepository;
    vector<User*> users;
    User* currentUser;
	set<int> loggedInUserIds;
};

#endif
