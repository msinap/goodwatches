#ifndef USER_H
#define USER_H

#include "utility.h"

class UserRepository;
class FilmRepository;

class User {
public:
    User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr);
    string getUsername();
    string getPassword();
    string getEmail();
    void follow(Map &parameters);
	void buyFilm(Map &parameters);
	void addMoney(Map &parameters);
	void rateFilm(Map &parameters);
	void showFilm(Map &parameters);
    void findFilms(Map &parameters);
    void postComment(Map &parameters);
	virtual void collectEarning();
	virtual void addFollower(int id);
    virtual void postFilm(Map &parameters);
    virtual void editFilm(Map &parameters);
    virtual void deleteFilm(Map &parameters);
	virtual void replyComment(Map &parameters);
	virtual void deleteComment(Map &parameters);
    virtual void outputFollowers(Map &parameters);
    virtual void outputPublishedFilms(Map &parameters);
protected:
    Map data;
    int id;
	int money;
	set<int> purchasedFilmIds;
    UserRepository* userRepository;
    FilmRepository* filmRepository;
};

#endif
