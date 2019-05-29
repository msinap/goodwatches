#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "utility.h"
#include "User.h"

class UserRepository;

class Publisher : public User {
public:
    Publisher(Map &parameters, int id, UserRepository* ur, FilmRepository* fr);
	virtual void collectEarning();
	virtual bool addFollower(int id);
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

    set<int> publishedFilmIds;
    set<int> followerIds;
};

#endif
