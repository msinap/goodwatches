#include "NotificationsRepository.h"

NotificationsRepository::NotificationsRepository() 
	: lastReadNotificationId(0) {
	notifications.push_back(NULL);
}

void NotificationsRepository::addNotification(Notification* newNotification) {
	notifications.push_back(newNotification);
}

void NotificationsRepository::outputLastReadNotifications(Map &parameters) {
	checkMustHave({"limit"}, parameters);
	checkMayHave({"limit"}, parameters);
	int limit = stringToInt(parameters["limit"]);

	vector<vector<string>> output;
	for (int id = lastReadNotificationId; id > 0 && limit > 0; id --, limit --) {
		string NotificationOutput = getNotificationById(id)->getOutput();
		output.push_back(vector<string> (1, NotificationOutput));
	}
	print({"Notification Message"},output , "");
}

void NotificationsRepository::outputAllUnreadNotifications() {
	vector<vector<string>> output;
	for (int id = notifications.size() - 1; id > lastReadNotificationId; id --) {
		string NotificationOutput = getNotificationById(id)->getOutput();
		output.push_back(vector<string> (1, NotificationOutput));
	}
	print({"Notification Message"}, output, "");
	readAllNotifications();
}

void NotificationsRepository::readAllNotifications() {
	lastReadNotificationId = notifications.size() - 1;
}

Notification* NotificationsRepository::getNotificationById(int id) {
	if (id <= 0 || id >= notifications.size())
		throw NotFoundError();
	return notifications[id];
}



