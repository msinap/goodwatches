#include "UserRepository.h"

void UserRepository::addUser(vector<string> &remainingWordsOfLine) {
    if(getAndPopBack(remainingWordsOfLine) != "email")
        throw BadRequestError();
    string email = getAndPopBack(remainingWordsOfLine);

    if (getAndPopBack(remainingWordsOfLine) != "username")
        throw BadRequestError();
    string username = getAndPopBack(remainingWordsOfLine);
    if(isUsernameExisted(username))
        throw BadRequestError();

    if (getAndPopBack(remainingWordsOfLine) != "password")
        throw BadRequestError();
    string password = getAndPopBack(remainingWordsOfLine);

    if (getAndPopBack(remainingWordsOfLine) != "age")
        throw BadRequestError();
    string age = getAndPopBack(remainingWordsOfLine);

    if (remainingWordsOfLine.empty()) {
        users.push_back(new User(email, username, password, age, users.size()+1));
        return;
    }

    if (getAndPopBack(remainingWordsOfLine) != "publisher")
        throw BadRequestError();
    string isPublisher = getAndPopBack(remainingWordsOfLine);
    if (isPublisher == "true") {
        users.push_back(new Publisher(email, username, password, age, users.size()+1));
    }else if(isPublisher == "false"){
        users.push_back(new User(email, username, password, age, users.size()+1));
    }else {
        throw BadRequestError();
    }
}

bool UserRepository::isUsernameExisted(string username) {
    for (User* user : users)
        if (user->getUsername() == username)
            return true;
    return false;
}
