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

class CollectMoneyHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class BuyHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class DeleteHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class RateHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class AddCommentHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

class ProfileHandler : public TemplateHandler {
public:
    ProfileHandler(std::string filePath);
    std::map<std::string, std::string> handle(Request *req);
};

class HomeHandler : public TemplateHandler {
public:
    HomeHandler(std::string filePath);
    std::map<std::string, std::string> handle(Request *req);
};

class PublisherHandler : public TemplateHandler {
public:
    PublisherHandler(std::string filePath);
    std::map<std::string, std::string> handle(Request *req);
};

class FilmHandler : public TemplateHandler {
public:
    FilmHandler(std::string filePath);
    std::map<std::string, std::string> handle(Request *req);
};

class AdminHandler : public TemplateHandler {
public:
    AdminHandler(std::string filePath);
    std::map<std::string, std::string> handle(Request *req);
};

string makeHtmlOfFilms(vector<int> ids, bool detailed = true, string linkType = "film");

string makeTableOfFilm(int id, bool detailed, string linkType = "film");

string makeHtmlOfcomments(vector<string> comments);

#endif