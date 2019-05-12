#include "User.h"
#include "UserRepository.h"
#include "FilmRepository.h"

User::User(Map &parameters, int _id, UserRepository* ur, FilmRepository* fr)
    : data(parameters), id(_id), userRepository(ur), filmRepository(fr) {
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

void User::postFilm(Map &parameters) {
    throw PermissionDeniedError();
}
void User::editFilm(Map &parameters) {
    throw PermissionDeniedError();
}
void User::deleteFilm(Map &parameters) {
    throw PermissionDeniedError();
}
