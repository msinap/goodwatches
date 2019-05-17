#include "Notifications.h"

Notification::Notification(string _username, int _userId) 
	: username(_username), userId(_userId) {
}

ReplyToYourCommentNotification::ReplyToYourCommentNotification(string _username, int _userId)
	: Notification(_username, _userId) {
}
RegisterNewFilmNotification::RegisterNewFilmNotification(string _username, int _userId)
	: Notification(_username, _userId) {
}
FollowYouNotification::FollowYouNotification(string _username, int _userId)
	: Notification(_username, _userId) {
}
BuyYourFilmNotification::BuyYourFilmNotification(string _username, int _userId, string _filmName, int _filmId)
	: Notification(_username, _userId), filmName(_filmName), filmId(_filmId) {
}
RateYourFilmNotification::RateYourFilmNotification(string _username, int _userId, string _filmName, int _filmId)
	: Notification(_username, _userId), filmName(_filmName), filmId(_filmId) {
}
CommentOnYourFilmNotification::CommentOnYourFilmNotification(string _username, int _userId, string _filmName, int _filmId)
	: Notification(_username, _userId), filmName(_filmName), filmId(_filmId) {
}

string ReplyToYourCommentNotification::getOutput() {
	return "Publisher " + username + " with id " + intToString(userId) + " reply to your comment.";
}
string RegisterNewFilmNotification::getOutput() {
	return "Publisher " + username + " with id " + intToString(userId) + " register new film";
}
string FollowYouNotification::getOutput() {
	return "User " + username + " with id " + intToString(userId) + " follow you.";
}
string BuyYourFilmNotification::getOutput() {
	return "User " + username + " with id " + intToString(userId) + " buy your film " + filmName + " with id " + intToString(filmId) + ".";
}
string RateYourFilmNotification::getOutput() {
	return "User " + username + " with id " + intToString(userId) + " rate your film " + filmName + " with id " + intToString(filmId) + ".";
}
string CommentOnYourFilmNotification::getOutput() {
	return "User " + username + " with id " + intToString(userId) + " comment on your film " + filmName + " with id " + intToString(filmId) + ".";
}