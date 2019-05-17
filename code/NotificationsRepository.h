#ifndef NOTIFICATIONSREPOSITORY_H
#define NOTIFICATIONSREPOSITORY_H

#include "utility.h"
#include "Notifications.h"

class NotificationsRepository {
public:
	NotificationsRepository();
	void addNotification(Notification* newNotification);
	void outputLastReadNotifications(Map &parameters);
	void outputAllUnreadNotifications();
	void readAllNotifications();
private:
	Notification* getNotificationById(int id);

	vector<Notification*> notifications;
	int lastReadNotificationId;
};

#endif