#ifndef USER_H
#define USER_H

#include "utility.h"

class UserRepository;
class FilmRepository;
class NotificationsRepository;

class User {
public:
	User();
    User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr);
	NotificationsRepository* getNotificationsRepository();
    string getUsername();
    string getPassword();
    string getEmail();
	int getId();
	
	virtual bool isPublisher();
	virtual string getMoney();
    
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
	virtual vector<int> findInPurchasedFilms(Map &parameters);
	virtual vector<int> getRecommendedFilmIds(Map &parameters);
	
	virtual void collectEarning();
	virtual bool addFollower(int id);
	virtual string getUncollectedMoney();
    virtual void postFilm(Map &parameters);
    virtual void editFilm(Map &parameters);
    virtual void deleteFilm(Map &parameters);
	virtual void replyComment(Map &parameters);
	virtual void deleteComment(Map &parameters);
    virtual void outputFollowers(Map &parameters);
    virtual void outputPublishedFilms(Map &parameters);
	virtual vector<int> findInPublishedFilms(Map &parameters);
protected:
	int getAndCheckFilmId(Map &parameters);

    Map data;
    int id;
	int money;
	set<int> purchasedFilmIds;
    UserRepository* userRepository;
    FilmRepository* filmRepository;
	NotificationsRepository* notificationsRepository;
};

#endif
