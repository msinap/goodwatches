#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include "utility.h"

class Notification {
public:
	Notification(string _username, int _userId);
	virtual string getOutput() = 0;
protected:
	string username;
	int userId;
};

class ReplyToYourCommentNotification : public Notification {
public:
	ReplyToYourCommentNotification(string _username, int _userId);
	virtual string getOutput();
};

class RegisterNewFilmNotification : public Notification {
public:
	RegisterNewFilmNotification(string _username, int _userId);
	virtual string getOutput();
};

class FollowYouNotification : public Notification {
public:
	FollowYouNotification(string _username, int _userId);
	virtual string getOutput();
};

class BuyYourFilmNotification : public Notification {
public:
	BuyYourFilmNotification(string _username, int _userId, string _filmName, int _filmId);
	virtual string getOutput();
private:
	string filmName;
	int filmId;
};

class RateYourFilmNotification : public Notification {
public:
	RateYourFilmNotification(string _username, int _userId, string _filmName, int _filmId);
	virtual string getOutput();
private:
	string filmName;
	int filmId;
};

class CommentOnYourFilmNotification : public Notification {
public:
	CommentOnYourFilmNotification(string _username, int _userId, string _filmName, int _filmId);
	virtual string getOutput();
private:
	string filmName;
	int filmId;
};

#endif