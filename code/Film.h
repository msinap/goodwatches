#ifndef FILM_H
#define FILM_H

#include "utility.h"

class CommandManager;
class Publisher;

class Film {
public:
    Film(Map &parameters);
    void edit(Map &parameters);
private:
    Map data;
    bool isForSale;
};

#endif
