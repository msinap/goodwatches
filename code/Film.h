#ifndef FILM_H
#define FILM_H

#include "utility.h"

class CommandManager;
class Publisher;

class Film {
public:
    Film(Map &parameters, Publisher* _owner, int _id);
private:
    Map data;
    int id;
    Publisher* owner;
};

#endif
