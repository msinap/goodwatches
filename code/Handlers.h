#ifndef HANDLERS_H
#define HANDLERS_H

#include "../server/server.hpp"
#include "utility.h"
#include "UserRepository.h"
#include "FilmRepository.h"

class SignupHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class LogoutHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class LoginHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class StartHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class AddFilmHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class AddMoneyHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class ProfileHandler : public TemplateHandler {
public:
    ProfileHandler(std::string filePath);
    std::map<std::string, std::string> handle(Request *req);
};


string makeHtmlOfFilms(vector<int> ids, bool detailed = true);

string makeTableOfFilm(int id, bool detailed);

#endif