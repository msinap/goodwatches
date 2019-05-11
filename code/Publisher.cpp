#include "Publisher.h"

Publisher::Publisher(string _email, string _username, string _password, string _age, int _id)
    : User(_email, _username, _password, _age, _id) {
}

UserType Publisher::getType() {
    return UserType::Publisher;
}
