#ifndef FILM_H
#define FILM_H

#include "utility.h"

class CommandManager;
class Publisher;

class Film {
public:
    Film(Map &parameters);
    void edit(Map &parameters);
    void stopSale(Map &parameters);
    Map getData();
    bool isForSale();
private:
    Map data;
    bool forSale;
};

#endif
