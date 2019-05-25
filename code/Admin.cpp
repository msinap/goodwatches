#include "Admin.h"

Admin::Admin(FilmRepository* fr) {
	filmRepository = fr;
	data["username"] = "admin";
	data["password"] = hashFletcherCRC("admin");
}

void Admin::outputMoney() {
	int benefit = filmRepository->getSumOfAdminShares();
	int uncollectedMoneyOfPublishers = filmRepository->getSumOfUncollectedMoney();
	print(vector<string> (1, intToString(benefit + uncollectedMoneyOfPublishers)));
}

void Admin::makeAllNotificationsRead() {
	
}
NotificationsRepository* Admin::getNotificationsRepository() {
	throw PermissionDeniedError();
}
void Admin::follow(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::buyFilm(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::seeUnreadNotifications() {
	throw PermissionDeniedError();
}
void Admin::addMoney(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::rateFilm(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::showFilm(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::findFilms(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::postComment(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::seeReadNotifications(Map &parameters) {
	throw PermissionDeniedError();
}
void Admin::outputPurchasedFilms(Map &parameters) {
	throw PermissionDeniedError();
}