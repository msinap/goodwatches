#include "Publisher.h"

Publisher::Publisher(Map &parameters, int _id, UserRepository* r)
    : User(parameters, id, r) {
}

UserType Publisher::getType() {
    return UserType::Publisher;
}
