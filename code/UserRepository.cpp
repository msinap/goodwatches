#include "UserRepository.h"

void UserRepository::addUser(vector<string> &remainingWordsOfLine) {
    if(getAndPopBack(remainingWordsOfLine) != "email")
        throw NotFoundError();
    string email = getAndPopBack(remainingWordsOfLine);
    if (getAndPopBack(remainingWordsOfLine) != "username")
        throw NotFoundError();
    string username = getAndPopBack(remainingWordsOfLine);
    if (getAndPopBack(remainingWordsOfLine) != "password")
        throw NotFoundError();
    string password = getAndPopBack(remainingWordsOfLine);
    if (getAndPopBack(remainingWordsOfLine) != "age")
        throw NotFoundError();
    string age = getAndPopBack(remainingWordsOfLine);

    if (remainingWordsOfLine.empty()) {
        users.push_back(new User(email, username, password, age, users.size()+1));
        return;
    }

    if (getAndPopBack(remainingWordsOfLine) != "publisher")
        throw NotFoundError();
    string isPublisher = getAndPopBack(remainingWordsOfLine);
    if (isPublisher == "true") {

    }else if(isPublisher == "false"){
        users.push_back(new User(email, username, password, age, users.size()+1));
    }else {
        throw NotFoundError();
    }
}
