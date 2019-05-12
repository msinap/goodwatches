#include "User.h"
#include "UserRepository.h"

User::User(Map &parameters, int _id, UserRepository* r)
    : data(parameters), id(_id), userRepository(r) {
    checkMustHave({"email", "username", "password", "age"}, data);
    checkMayHave ({"email", "username", "password", "age", "publisher"}, data);
    //TODO checkEmail(parameters["email"]);
    if(userRepository->findUserWithUsername(data["username"]) != NULL)
        throw BadRequestError();
    checkNumeric(parameters["age"]);
    addLeadingZeros(parameters["age"]);
}

string User::getUsername() {
    return data["username"];
}

string User::getPassword() {
    return data["password"];
}

UserType User::getType() {
    return UserType::Normal;
}
