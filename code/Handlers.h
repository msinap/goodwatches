#ifndef HANDLERS_H
#define HANDLERS_H

#include "../server/server.hpp"
#include "utility.h"
#include "CommandManager.h"
#include "UserRepository.h"
#include "FilmRepository.h"

class SignupHandler : public RequestHandler {
public:
    Response* callback(Request*);
};

#endif