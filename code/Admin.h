#ifndef ADMIN_H
#define ADMIN_H

#include "utility.h"
#include "User.h"
#include "FilmRepository.h"

class Admin : public User {
public:
    Admin(FilmRepository* fr);
	virtual string getMoney();

	virtual NotificationsRepository* getNotificationsRepository();
    virtual void follow(Map &parameters);
	virtual void buyFilm(Map &parameters);
	virtual void seeUnreadNotifications();
	virtual void addMoney(Map &parameters);
	virtual void rateFilm(Map &parameters);
	virtual void showFilm(Map &parameters);
	virtual void makeAllNotificationsRead();
    virtual void postComment(Map &parameters);
	virtual vector<int> findFilms(Map &parameters);
	virtual void seeReadNotifications(Map &parameters);
	virtual void outputPurchasedFilms(Map &parameters);
protected:
	int getAndCheckFilmId(Map &parameters);
};

#endif